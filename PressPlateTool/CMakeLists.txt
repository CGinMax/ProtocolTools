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
find_package(Qt5 COMPONENTS Core Qml Quick QuickControls2 REQUIRED)
find_package(Qt5QuickCompiler)

include_directories(../Qaterial/include)
include_directories(../Communication)
set(QML_IMPORT_PATH ${CMAKE_CURRENT_BINARY_DIR}/../ CACHE STRING "qml import path")

# Not use qt5_add_resources,
set(QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.qrc)
#qt5_add_resources(QRC_FILES qml.qrc)

# Add qml to the qtquick compiler
qtquick_compiler_add_resources(QUICK_QRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/resources/resources.qrc)

add_executable(${PROJECT_NAME}
qmlmain.cpp
${QRC_FILES}
${QUICK_QRC_FILES}
)

target_link_libraries(${PROJECT_NAME} PUBLIC
Threads::Threads
Communication
Qaterial
Qt5::Core
Qt5::Qml
Qt5::Quick
Qt5::QuickControls2
)
