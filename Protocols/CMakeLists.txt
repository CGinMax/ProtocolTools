cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(Protocols)

# 编译类型选项
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/debug)
else()
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

add_definitions(-DPROTOCOLS_LIBRARY)

add_subdirectory(YBProtocol)

add_library(${PROJECT_NAME}
STATIC
    protocols_global.h
    iprotocols.h
    convert.h
    iprotocols.cpp
    convert.cpp
)

target_link_libraries(${PROJECT_NAME} PUBLIC
YBProtocol
)
