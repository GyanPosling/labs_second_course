cmake_minimum_required(VERSION 3.12.0)

project(lab2)

include_directories(include)

set(SOURCES_PARENT 
    src/parent/main.c
    src/environment.c
)

set(SOURCES_CHILD 
    src/child/main.c
    src/environment.c
)

set(HEADERS
    include/environment.h
)

add_executable(parent ${SOURCES_PARENT} ${HEADERS})

add_executable(child ${SOURCES_CHILD} ${HEADERS})