cmake_minimum_required(VERSION 3.20)
project(hw_2 C CXX)

option(parallel "build" OFF)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread ")



set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -Wall -Wpedantic -Werror --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wpedantic -Werror --coverage")

add_library(input_data STATIC project/input_data.c)
target_include_directories(input_data PUBLIC project)

add_library(consistent STATIC project/prog.c )
target_include_directories(consistent PUBLIC project)
target_link_libraries(consistent PUBLIC input_data)

add_library(parallel SHARED project/parallel_prog.c)
target_include_directories(parallel PUBLIC project)
target_link_libraries(parallel PUBLIC input_data)

add_executable(hw_2 project/main.c )

if(parallel)
    message("parallel")
    target_link_libraries(hw_2  parallel )
else()
    message("consistent")
    target_link_libraries(hw_2   consistent)
endif(parallel)

find_package(GTest REQUIRED)

add_executable(tests tests/prog_test.cpp tests/input_test.cpp )
target_link_libraries(tests GTest::gtest consistent input_data)

add_executable(tests_parallel tests/parallel_prog_test.cpp tests/input_test.cpp)
target_link_libraries(tests_parallel GTest::gtest  parallel input_data)

add_executable(comparison tests/comparison.cpp )
target_link_libraries(comparison GTest::gtest)
