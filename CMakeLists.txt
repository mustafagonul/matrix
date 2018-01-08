cmake_minimum_required(VERSION 2.8)
project(matrix-cpp)

# Compiler Flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Library source files
set(SOURCE_FILES matrix.cpp)

# Library
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

# Setup testing
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

# Test source files
set(TEST_SOURCE_FILES test/matrix.cpp test/main.cpp)

# Test executable
add_executable(matrix-cpp-test ${TEST_SOURCE_FILES})
target_link_libraries(matrix-cpp-test ${CMAKE_CURRENT_BINARY_DIR}/libmatrix-cpp.a ${GTEST_BOTH_LIBRARIES})

# Test directive 
add_test(NAME matrix-cpp-test COMMAND matrix-cpp-test)
