set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE ON)#?

set(EXE_NAME CdtTools)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Threads)
find_package(Qt5 COMPONENTS Widgets Core Gui Network Concurrent LinguistTools)

set(TS_FILES CdtTools_en.ts CdtTools_zh.ts)

add_subdirectory(common)
add_subdirectory(network)
add_subdirectory(protocol)
add_subdirectory(ui)

add_executable(${EXE_NAME} main.cpp)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

target_link_libraries(${EXE_NAME} Threads::Threads)
target_link_libraries(${EXE_NAME} 
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


target_link_libraries(${EXE_NAME} qt-material-widgets)