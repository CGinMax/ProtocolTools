cmake_minimum_required(VERSION 3.15.0 FATAL_ERROR)
project(Communication)

# 编译类型选项
if (CMAKE_BUILD_TYPE STREQUAL Debug)
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/debug)
else()
    set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../cmake-bin/release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_AUTOMOC ON)

add_definitions(-DCOMMUNICATION_LIBRARY)

find_package(Qt5 COMPONENTS Core Network SerialPort REQUIRED)

set(NETWORK_SRC
    communication_global.h
    communicationbase.h
    communicationbase.cpp
    portparam.h
    portparam.cpp
    serialport.h
    serialport.cpp
    tcpclient.h
    tcpclient.cpp
    tcpserver.h
    tcpserver.cpp
    udpsocket.h
    udpsocket.cpp
    qmlserialporthelper.h
    qmlserialporthelper.cpp
)

add_library(${PROJECT_NAME} STATIC ${NETWORK_SRC})
#target_
target_link_libraries(${PROJECT_NAME} PUBLIC Qt5::Core Qt5::Network Qt5::SerialPort)
