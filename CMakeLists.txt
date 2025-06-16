cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(this metrics)
project(${this})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pthread")




enable_testing()
add_subdirectory(tests)


file(GLOB headers "include/*.hpp")
file(GLOB sources "src/*.cpp")

add_library(${this} STATIC ${sources} ${headers})

add_subdirectory(examples)