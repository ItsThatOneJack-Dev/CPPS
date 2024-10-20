#include <chrono>
#include <csignal>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <ranges>

#include "modulesource.cpp"
#include "processinterface.hpp"
#include "timeutils.cpp"
#include "which.cpp"

std::string PromptLine1 = "C++S " + std::filesystem::current_path().string();
std::string PromptLine2 = "\u276F";

std::string Command;

void signalHandler(const int signum) {
    std::cout << "\nExiting shell...\n";
    exit(signum);
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");

    return (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

// Function to split a string by a delimiter and return a vector of substrings
std::vector<std::string> splitbydelim(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;

    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }

    return tokens;
}

std::string toLower(const std::string& str) {
    std::string lowerStr = str; // Make a copy of the original string
    std::ranges::transform(lowerStr, lowerStr.begin(),
                           [](unsigned char c) { return std::tolower(c); }); // Convert each character to lowercase
    return lowerStr;
}

// Function to split a command string by '|' and then by spaces
std::vector<std::vector<std::string>> parseCommands(const std::string& input) {
    std::vector<std::vector<std::string>> commands;

    // Split the input by the pipe symbol '|'
    std::vector<std::string> segments = splitbydelim(input, '|');

    // For each segment, split it by spaces and add to commands list
    for (const auto& segment : segments) {
        // Split by spaces
        std::vector<std::string> args = splitbydelim(segment, ' ');

        // Add non-empty command (ignore empty commands from excess spaces)
        if (!args.empty()) {
            commands.push_back(args);
        }
    }

    return commands;
}

int main() {
    std::signal(SIGINT, signalHandler);

    while (true) {
        std::cout << PromptLine1 << std::endl;
        std::cout << PromptLine2;
        std::getline(std::cin, Command);

        std::vector CallData = parseCommands(Command);
        std::vector<std::string> args(CallData[0].begin() + 1, CallData[0].end());

        std::string command = CallData[0][0];

        if (toLower(command) == "exit") {
            break;
        } if (toLower(command) == "clear") {
            std::cout << "\033[2J\033[1;1H";
            continue;
        } if (toLower(command) == "time" || toLower(command) == "date") {
            std::cout << "It is: " << TimeUtils::todayDate("D/M/Y") << " at " << TimeUtils::secondAccuracy() << std::endl;
            std::cout << "Using date format: DD/MM/YYYY." << std::endl;
            continue;
        }
        if (command.empty()) {
            continue;
        }

        std::cout << "[+] Which: Located binary at: `" << which(Command) << "`." << std::endl;

        Process proc(command, args);

        // Poll the process for output while it is running
        while (proc.isRunning()) {
            proc.readFromStdout();
            proc.readFromStderr();
            std::cout << proc.flushOutput();
            std::cerr << proc.flushErrorOutput();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        // Final flush after the process exits
        proc.readFromStdout();
        proc.readFromStderr();
        std::cout << proc.flushOutput();
        std::cerr << proc.flushErrorOutput();
    }

    return 0;
}
