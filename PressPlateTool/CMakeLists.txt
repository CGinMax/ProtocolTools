cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)

project(PressPlateTool)

# 编译类型选项
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/debug)
else()
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


find_package(Threads)
find_package(Qt5 REQUIRED COMPONENTS Core Qml Quick QuickControls2 SerialPort)
find_package(Qt5QuickCompiler)
find_package(Qt5LinguistTools)

add_subdirectory(common)
add_subdirectory(protocol)
add_subdirectory(model)
add_subdirectory(controller)
include_directories(../Qaterial/include)
include_directories(../Communication)
include_directories(../QtAwesome)
include_directories(model)
include_directories(common)
include_directories(controller)
include_directories(protocol)

qt5_create_translation(TS_FILES
    # ${CMAKE_CURRENT_SOURCE_DIR}/resources/qml
    ${CMAKE_CURRENT_SOURCE_DIR}
    PressPlateTool_zh.ts
    PressPlateTool_en.ts
)

set(QML_IMPORT_PATH ${CMAKE_CURRENT_BINARY_DIR}/../ CACHE STRING "qml import path")

# Not use qt5_add_resources,
set(QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.qrc)
#qt5_add_resources(QRC_FILES qml.qrc)

# Add qml to the qtquick compiler
qtquick_compiler_add_resources(QUICK_QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.qrc)

set(PressPlateToolSrc
    main.cpp
    qmlexport.h
    qmlexport.cpp
)

add_executable(${PROJECT_NAME}
    ${PressPlateToolSrc}
    ${QRC_FILES}
    ${QUICK_QRC_FILES}
    ${TS_FILES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
    Threads::Threads
    qtasyncfuture
    QtAwesome
    Communication
    Protocols
    Qaterial
    common
    model
    protocol
    controller
    Qt5::Core
    Qt5::Qml
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::SerialPort
)
