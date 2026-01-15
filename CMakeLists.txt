cmake_minimum_required(VERSION 3.31)
project(Drexel_University_CS_441_Compiler_Implementation)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Drexel_University_CS_441_Compiler_Implementation
        include/Token.h
        include/TokenType.h
        src/main.cpp
        include/Tokenizer.h
        src/Tokenizer.cpp
        include/Parser.h
        include/expr.h
        src/Parser.cpp)
