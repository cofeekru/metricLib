cmake_minimum_required(VERSION 3.13 FATAL_ERROR)



set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pthread")

project(metrics)

include_directories(include)

add_executable(main main.cpp src/metricsLib.cpp)