cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(CdtTools CXX)

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)#?

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Threads)
find_package(Qt5 COMPONENTS Widgets Core Gui Network Concurrent LinguistTools)

# 编译类型选项
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/debug)
else()
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(TS_FILES CdtTools_en.ts CdtTools_zh.ts)

add_subdirectory(common)
add_subdirectory(network)
add_subdirectory(protocol)
add_subdirectory(ui)

add_executable(${PROJECT_NAME} 
    main.cpp
    enums.h
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME} 
    Qt5::Core 
    Qt5::Widgets 
    Qt5::Gui 
    Qt5::Network 
    Qt5::Concurrent
    common
    network
    protocol
    ui
)


target_link_libraries(${PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/libqt-material-widgets.a)