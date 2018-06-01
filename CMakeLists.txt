cmake_minimum_required(VERSION 3.11)
project(ParallelProgramming)

set(CMAKE_CXX_FLAGS -std=c++17)
set(CMAKE_CXX_STANDARD 17)

add_executable(ParallelProgramming main.cpp thread_demo.hpp type_definitions.hpp benchmarking_runs.hpp general_coding.hpp compiler_test_code.hpp)