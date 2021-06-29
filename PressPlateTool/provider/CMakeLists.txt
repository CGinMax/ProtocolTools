set(SUBDIR_NAME provider)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Qml
    Quick
)

set(CMAKE_AUTOMOC ON)
include_directories(../../QtAwesome)
add_library(${SUBDIR_NAME}
STATIC
    faiconprovider.h
    faiconprovider.cpp
)

target_link_libraries(${SUBDIR_NAME}
PUBLIC
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Qml
    Qt5::Quick
    QtAwesome
)
