cmake_minimum_required(VERSION 3.24)
project(Regular_Expression_to_Lambda_NFA)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Regular_Expression_to_Lambda_NFA
        lambda-nfa.cpp
        lambda-nfa.h
        regular-expression.cpp
        regular-expression.h main.cpp)
