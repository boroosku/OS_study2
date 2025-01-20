cmake_minimum_required(VERSION 3.10)

# Указываем название проекта
project(myprog2)

# Устанавливаем флаг для C++14
set(CMAKE_CXX_STANDARD 14)

# Указываем каталоги для исходных кодов и заголовков
include_directories(include)

# Добавляем библиотеку
add_library(process_launcher STATIC src/process_launcher.cpp)

# Добавляем тестовую утилиту
add_executable(myprog2 src/main.cpp)

# Линкуем утилиту с библиотекой
target_link_libraries(myprog2 process_launcher)
