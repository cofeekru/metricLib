cmake_minimum_required(VERSION 3.13)

set(this metricsTests)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_executable(${this} metricsTests.cpp)

target_link_libraries(${this} PUBLIC 
    gtest_main 
    metrics
)

add_test(NAME metricsLibTests COMMAND metricsTests)