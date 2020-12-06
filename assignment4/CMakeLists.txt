cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-O3 -march=native")

project(mymatrix)

SET(SRC_LIST main.cpp matrix.cpp)
add_executable(use_matrix ${SRC_LIST})

 
MESSAGE(STATUS "END")
