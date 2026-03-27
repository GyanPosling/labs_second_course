cmake_minimum_required(VERSION 3.10)
project(dirwalk C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

add_executable(dirwalk
    main.c
    dirwalk.c
    pathlist.c
)

target_compile_options(dirwalk PRIVATE -Wall -Wextra -Wpedantic)
