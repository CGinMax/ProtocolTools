cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)
project(qt-material-widgets CXX)

find_package(Qt5 REQUIRED COMPONENTS Core Gui Widgets)

# set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../bin/lib)

aux_source_directory(. MATERIAL_WIDGETS_SRC)
add_library(qt-material-widgets
STATIC 
    $<TARGET_OBJECTS:lib>
    $<TARGET_OBJECTS:layouts>
    ${MATERIAL_WIDGETS_SRC}
)


add_subdirectory(layouts)
add_subdirectory(lib)

target_include_directories(qt-material-widgets PUBLIC .)
target_include_directories(qt-material-widgets PUBLIC ./layouts)
target_include_directories(qt-material-widgets PUBLIC ./lib)

target_link_libraries(qt-material-widgets PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)
