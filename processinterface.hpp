#ifndef PROCESSINTERFACE_H
#define PROCESSINTERFACE_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#endif

class Process {
private:
    std::string output;
    std::string error_output;
#ifdef _WIN32
    HANDLE child_stdout_read = nullptr;
    HANDLE child_stdout_write = nullptr;
    HANDLE child_stderr_read = nullptr;
    HANDLE child_stderr_write = nullptr;
    HANDLE child_stdin_read = nullptr;
    HANDLE child_stdin_write = nullptr;
    PROCESS_INFORMATION proc_info{};
#else
    int stdout_fd[2];
    int stderr_fd[2];
    int stdin_fd[2];
    pid_t pid;
#endif

public:
    Process(const std::string& command, const std::vector<std::string>& args) {
#ifdef _WIN32
        // Create pipes for stdout, stderr
        SECURITY_ATTRIBUTES saAttr;
        saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
        saAttr.bInheritHandle = TRUE;
        saAttr.lpSecurityDescriptor = nullptr;

        if (!CreatePipe(&child_stdout_read, &child_stdout_write, &saAttr, 0) ||
            !CreatePipe(&child_stderr_read, &child_stderr_write, &saAttr, 0) ||
            !SetHandleInformation(child_stdout_read, HANDLE_FLAG_INHERIT, 0) ||
            !SetHandleInformation(child_stderr_read, HANDLE_FLAG_INHERIT, 0)) {
            throw std::runtime_error("Error creating pipes");
        }

        // Set up command line
        std::string cmd = command;
        for (const auto& arg : args) {
            cmd += " " + arg;
        }

        STARTUPINFOA si;
        ZeroMemory(&si, sizeof(STARTUPINFO));
        si.cb = sizeof(STARTUPINFO);
        si.hStdError = child_stderr_write;
        si.hStdOutput = child_stdout_write;
        si.hStdInput = nullptr;
        si.dwFlags |= STARTF_USESTDHANDLES;

        ZeroMemory(&proc_info, sizeof(PROCESS_INFORMATION));

        if (!CreateProcessA(nullptr, const_cast<LPSTR>(cmd.c_str()), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &proc_info)) {
            throw std::runtime_error("Failed to create process");
        }
#else
        // Unix-specific code (omitted for simplicity)
#endif
    }

    ~Process() {
#ifdef _WIN32
        CloseHandle(proc_info.hProcess);
        CloseHandle(proc_info.hThread);
        CloseHandle(child_stdout_read);
        CloseHandle(child_stdout_write);
        CloseHandle(child_stderr_read);
        CloseHandle(child_stderr_write);
#endif
    }

    [[nodiscard]] bool isRunning() const {
#ifdef _WIN32
        DWORD exit_code;
        GetExitCodeProcess(proc_info.hProcess, &exit_code);
        return exit_code == STILL_ACTIVE;
#else
        int status;
        return waitpid(pid, &status, WNOHANG) == 0;
#endif
    }

    void readFromStdout() {
#ifdef _WIN32
        DWORD bytesRead;
        CHAR buffer[1024];
        if (PeekNamedPipe(child_stdout_read, nullptr, 0, nullptr, &bytesRead, nullptr) && bytesRead > 0) {
            if (ReadFile(child_stdout_read, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
                buffer[bytesRead] = '\0';
                output += buffer;
            }
        }
#endif
    }

    void readFromStderr() {
#ifdef _WIN32
        DWORD bytesRead;
        CHAR buffer[1024];
        if (PeekNamedPipe(child_stderr_read, nullptr, 0, nullptr, &bytesRead, nullptr) && bytesRead > 0) {
            if (ReadFile(child_stderr_read, buffer, sizeof(buffer) - 1, &bytesRead, nullptr)) {
                buffer[bytesRead] = '\0';
                error_output += buffer;
            }
        }
#endif
    }

    [[nodiscard]] std::string getOutput() const {
        return output;
    }

    std::string flushOutput() {
        std::string current_output = output;
        output.clear();
        return current_output;
    }

    [[nodiscard]] std::string getErrorOutput() const {
        return error_output;
    }

    std::string flushErrorOutput() {
        std::string current_error_output = error_output;
        error_output.clear();
        return current_error_output;
    }
};
#endif