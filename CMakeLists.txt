cmake_minimum_required(VERSION 3.16)
project(CPP_project)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion -Wold-style-cast -Wnull-dereference")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")

set(SOURCES src/main.cpp src/process.cpp src/process_creator.cpp src/FCFS.cpp src/min_heap.cpp)
add_executable(executable ${SOURCES})
