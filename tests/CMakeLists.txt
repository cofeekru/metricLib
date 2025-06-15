cmake_minimum_required(VERSION 3.13)

set(this metricsTests)


add_executable(${this} metricsTests.cpp)

target_link_libraries(${this} PUBLIC gtest_main metrics)

add_test(NAME metricsTests COMMAND metricsTests)