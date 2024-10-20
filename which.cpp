#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <filesystem>
#include <algorithm>
#include <cctype>

// Utility function for case-insensitive comparison (if needed)
bool caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
    return std::equal(str1.begin(), str1.end(), str2.begin(), str2.end(),
                      [](char a, char b) {
                          return std::tolower(static_cast<unsigned char>(a)) ==
                                 std::tolower(static_cast<unsigned char>(b));
                      });
}

std::string which(const std::string& command) {
    const char* path_env = std::getenv("PATH");
    if (!path_env) {
        return "";  // PATH not set
    }

    std::istringstream path_stream(path_env);
    std::string path;

#ifdef _WIN32
    // Supported extensions on Windows (case-insensitive)
    const std::vector<std::string> extensions = {
        ".bat", ".bin", ".cmd", ".com", ".cpl", ".exe", ".gadget",
        ".inf1", ".ins", ".inx", ".isu", ".job", ".jse", ".lnk",
        ".msc", ".msi", ".msp", ".mst", ".paf", ".pif", ".ps1",
        ".reg", ".rgs", ".scr", ".sct", ".shb", ".shs", ".u3p",
        ".vb", ".vbe", ".vbs", ".vbscripts", ".ws", ".wsf", ".wsh"
    };
#endif

    // Loop through each directory in PATH
    while (std::getline(path_stream, path, ';')) {  // Use ';' as the delimiter for Windows
#ifdef _WIN32
        for (const auto& ext : extensions) {
            // Create the full path for the command

            // Check if the file exists and is a regular file
            if (std::string full_path = path + (path.back() == '\\' ? "" : "\\") += command + ext; std::filesystem::exists(full_path) && std::filesystem::is_regular_file(full_path)) {
                return full_path;  // Return the first matching path found
            }
        }
#else
        // For UNIX-like systems, just check the command name without extensions
        std::string full_path = path + "/" + command;
        if (std::filesystem::exists(full_path) && std::filesystem::is_regular_file(full_path)) {
            return full_path;  // Return the first matching path found
        }
#endif
    }

    return "";  // Not found
}
