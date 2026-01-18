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
        include/Expr.h
        src/Parser.cpp
        include/Stmnt.h
        include/AstPrinter.h
        src/AstPrinter.cpp
        include/Class.h
        include/Prog.h
        include/Basic.h
        include/IrControl.h
        include/IrStmnt.h
        include/Print.h
        include/IrValue.h
        include/Writer.h
        src/Writer.cpp
        include/IrGen.h
        src/IrGen.cpp)
