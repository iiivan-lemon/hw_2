cmake_minimum_required(VERSION 3.20)
project(hw2 C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )


set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS} -Wall -Wpedantic -Werror --coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -Wall -Wpedantic -Werror --coverage")

add_library(input_data STATIC project/input_data.c)
target_include_directories(input_data PUBLIC project)

add_library(consistent STATIC project/prog.c)
target_include_directories(consistent PUBLIC project)


add_executable(hw_2 project/main.c )
target_link_libraries(hw_2 input_data consistent)