cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)

project(
    structarus
    )

option(STRUCTARUS_TEST "Enable tests compiling" OFF)


if(STRUCTARUS_TEST)
    enable_testing()
    add_subdirectory(third_party/googletest-v1.15.2)
    add_subdirectory(tests)
endif()
