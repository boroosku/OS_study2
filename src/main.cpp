#include <iostream>
#include "process_launcher.hpp"

int main() {
    // Пример: запустим программу "echo" с аргументом
    int exitCode = ProcessLauncher::launch("echo", "Hello from myprog2!");
    std::cout << "Exit code of echo: " << exitCode << std::endl;

    // Пример для Windows: запуск программы, которая завершится с кодом 42
    #ifdef _WIN32
    exitCode = ProcessLauncher::launch("cmd.exe", "/C exit 42");
    std::cout << "Exit code of cmd.exe: " << exitCode << std::endl;
    #endif

    // Пример для Linux или macOS: запуск программы, которая завершится с кодом 99
    #ifndef _WIN32
    exitCode = ProcessLauncher::launch("bash", "-c 'exit 99'");
    std::cout << "Exit code of bash: " << exitCode << std::endl;
    #endif

    return 0;
}
