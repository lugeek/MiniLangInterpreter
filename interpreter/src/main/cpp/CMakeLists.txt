cmake_minimum_required(VERSION 3.10.2)

project(interpreter LANGUAGES C CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(minilang-interpreter
            SHARED
            native-lib.cpp
            main.cpp
            main_jni.cpp
            InputProgram.cpp
            lexer/lexer.cpp
            lexer/token.cpp
            parser/parser.cpp
            parser/ast.cpp
            visitor/xml_visitor.cpp
            visitor/semantic_analysis.cpp
            visitor/interpreter.cpp)

#add_executable(minilang
#        src/main.cpp
#        src/lexer/lexer.cpp
#        src/lexer/lexer.h
#        src/lexer/token.cpp
#        src/lexer/token.h
#        src/parser/parser.cpp
#        src/parser/parser.h
#        src/parser/ast.cpp
#        src/parser/ast.h
#        src/visitor/visitor.h
#        src/visitor/xml_visitor.cpp
#        src/visitor/xml_visitor.h
#        src/visitor/semantic_analysis.cpp
#        src/visitor/semantic_analysis.h
#        src/visitor/interpreter.cpp
#        src/visitor/interpreter.h
#        src/table/table.h)

target_link_libraries( minilang-interpreter
                       log )

#project(minilang)