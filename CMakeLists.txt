cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(this metrics)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pthread")

project(${this})

enable_testing()

add_subdirectory(googletest)

add_library(${this} STATIC src/metricsLib.cpp include/metricsLib.hpp)

add_subdirectory(tests)

add_executable(main main.cpp src/metricsLib.cpp)