include_directories(.)

add_executable(file_transfer
        control.cpp
        identify.cpp
        main.cpp
        protocol.c
        transport.cpp
        user.cpp)