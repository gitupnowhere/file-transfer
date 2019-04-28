include_directories(catch2 ../src)

add_executable(test_protocol
        test_protocol.cpp
        ../src/protocol.c)