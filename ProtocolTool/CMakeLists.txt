cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(ProtocolTool CXX)

set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)#?

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Threads)
find_package(Qt5 COMPONENTS Widgets Core Gui Network SerialPort Concurrent LinguistTools)

# 编译类型选项
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/debug)
else()
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(TS_FILES ProtocolTool_zh.ts ProtocolTool_en.ts)
set(QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)

add_subdirectory(common)
add_subdirectory(protocol)
add_subdirectory(ui)

add_executable(${PROJECT_NAME}
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    ${QRC_FILES}
)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(${PROJECT_NAME} Threads::Threads)
target_link_libraries(${PROJECT_NAME}
    Communication
    protocoltool_common
    protocoltool_protocol
    protocoltool_ui
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Network
    Qt5::Concurrent
    Qt5::SerialPort
)


# target_link_libraries(${PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/libqt-material-widgets.a)
