cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(qt-material-widgets CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# 编译类型选项
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/debug)
else()
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

aux_source_directory(. MATERIAL_WIDGETS_SRC)
add_library(${PROJECT_NAME}
STATIC 
    $<TARGET_OBJECTS:lib>
    $<TARGET_OBJECTS:layouts>
    ${MATERIAL_WIDGETS_SRC}
)


add_subdirectory(layouts)
add_subdirectory(lib)

target_include_directories(${PROJECT_NAME} PUBLIC .)
target_include_directories(${PROJECT_NAME} PUBLIC ./layouts)
target_include_directories(${PROJECT_NAME} PUBLIC ./lib)

target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)
