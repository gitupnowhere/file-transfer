cmake_minimum_required(VERSION 3.0)
project(file_transfer)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(file_transfer
        config.hpp
        control.cpp
        control.hpp
        identify.cpp
        identify.hpp
        main.cpp
        protocol.c
        protocol.h
        transmit.cpp
        transmit.hpp
        user.cpp
        user.hpp)
