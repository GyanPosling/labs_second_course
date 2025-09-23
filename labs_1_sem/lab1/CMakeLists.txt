cmake_minimum_required(VERSION 3.10)
project(MyStringProject)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main_exe 
    main.cpp 
    MyString.cpp 
    MyString.h
)