cmake_minimum_required(VERSION 3.13)
set(this metricsTests)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)




add_executable(${this} metricsTests.cpp)

target_link_libraries(${this} 
    PRIVATE
    GTest::GTest 
    metrics)

add_test(metricsGTests metricsTests)