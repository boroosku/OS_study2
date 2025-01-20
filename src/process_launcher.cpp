#include "process_launcher.hpp"
#include <iostream>

#ifdef _WIN32
int ProcessLauncher::launch(const std::string &program, const std::string &args) {
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    std::string command = "cmd.exe /C " + program + " " + args;
    if (CreateProcess(
        nullptr, 
        &command[0],  // команда в виде строки
        nullptr, nullptr, 
        FALSE, CREATE_NEW_CONSOLE, nullptr, nullptr, 
        &si, &pi
    )) {
        // Ожидаем завершения процесса
        WaitForSingleObject(pi.hProcess, INFINITE);

        // Получаем код завершения
        DWORD exitCode;
        GetExitCodeProcess(pi.hProcess, &exitCode);

        // Закрываем дескрипторы
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

        return exitCode;
    } else {
        DWORD error = GetLastError();
        std::cerr << "Failed to start process: " << error << std::endl;
        return -1;
    }
}

#else  // Для UNIX-подобных систем (Linux/macOS)

int ProcessLauncher::launch(const std::string &program, const std::string &args) {
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Failed to fork process" << std::endl;
        return -1;
    } else if (pid == 0) {  // Дочерний процесс
        int result = execlp(program.c_str(), program.c_str(), args.c_str(), nullptr);
        if (result == -1) {
            std::cerr << "Failed to execute program: " << strerror(errno) << std::endl;
        }
        return -1;
    } else {  // Родительский процесс
        int status;
        waitpid(pid, &status, 0);  // Ожидаем завершения процесса

        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);  // Возвращаем код завершения
        } else {
            std::cerr << "Process did not terminate normally" << std::endl;
            return -1;
        }
    }
}
#endif
