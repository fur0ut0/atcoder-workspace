cmake_minimum_required(VERSION 3.14)
project(atcoder_mylib)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.14.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 20)
set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(${TEST_NAME}
  test/prime.cpp
)
target_link_libraries(${TEST_NAME} gtest_main)
target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})

