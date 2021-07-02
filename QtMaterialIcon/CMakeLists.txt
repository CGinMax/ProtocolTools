cmake_minimum_required(VERSION 3.14.0)

project(QtMaterialIcon)

option(QTMATERIALICON_ENABLE_QML "make it enable use in qml" ON)
option(QTMATERIALICON_BUILD_SHARED "build material icon for shared library" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS 
	Core
	Gui
	Widgets
)

set(HEADERS 
	includes/qmaterialicon.h)

set(SOURCES 
	src/qmaterialicon.cpp)

if(QTMATERIALICON_ENABLE_QML)
	find_package(Qt5 REQUIRED COMPONENTS Qml Quick)
        list(APPEND HEADERS includes/materialiconprovider.h)
        list(APPEND SOURCES src/materialiconprovider.cpp)
endif()

qt5_add_resources(QRC ${CMAKE_CURRENT_SOURCE_DIR}/QMaterialIcon.qrc)
if(QTMATERIALICON_BUILD_SHARED)
        add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES} ${QRC})
else()
        add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCES} ${QRC})
endif()

set(LINKED_LIBRARIES Qt5::Core Qt5::Gui Qt5::Widgets)
if (QTMATERIALICON_ENABLE_QML)
	list(APPEND LINKED_LIBRARIES Qt5::Qml Qt5::Quick)
endif()
target_link_libraries(${PROJECT_NAME} PUBLIC ${LINKED_LIBRARIES})
