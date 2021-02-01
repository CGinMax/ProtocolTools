cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(CdtTools-Solution LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(CdtTools)

enable_testing()
add_subdirectory(test)
