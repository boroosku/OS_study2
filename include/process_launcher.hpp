#ifndef PROCESS_LAUNCHER_HPP
#define PROCESS_LAUNCHER_HPP

#include <string>

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

class ProcessLauncher {
public:
    // Функция запускает программу в фоновом режиме
    static int launch(const std::string &program, const std::string &args);

private:
    ProcessLauncher() = delete;
    ProcessLauncher(const ProcessLauncher&) = delete;
    ProcessLauncher& operator=(const ProcessLauncher&) = delete;
};
#endif // PROCESS_LAUNCHER_HPP
