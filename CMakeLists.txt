cmake_minimum_required(VERSION 3.0)
project(file_transfer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(file_transfer
        src/control.cpp
        src/identify.cpp
        src/main.cpp
        src/protocol.c
        src/transport.cpp
        src/user.cpp)