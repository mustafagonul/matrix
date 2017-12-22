cmake_minimum_required(VERSION 2.8)
project(matrix-cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES matrix.cpp)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})