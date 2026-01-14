cmake_minimum_required(VERSION 3.31)
project(Drexel_University_CS_441_Compiler_Implementation)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Drexel_University_CS_441_Compiler_Implementation
        include/token/Token.h
        include/token/TokenType.h
        src/main.cpp)
