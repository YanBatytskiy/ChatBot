cmake_minimum_required(VERSION 3.10)
project(ChatBot)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Рекурсивно ищем все cpp-файлы
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

# Создаём исполняемый файл
add_executable(chat_bot ${SOURCES})

# Укажем include-директории
target_include_directories(chat_bot PRIVATE src)