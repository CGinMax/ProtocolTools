set(SUBDIR_NAME controller)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

set(CMAKE_AUTOMOC ON)

include_directories(../../Communication)
include_directories(../model)
include_directories(../common)
include_directories(../protocol)

add_library(${SUBDIR_NAME}
STATIC
    gathercontroller.h
    gathercontroller.cpp
    controllermanager.h
    controllermanager.cpp
)

target_link_libraries(${SUBDIR_NAME}
PUBLIC
    Communication
    Protocols
    common
    model
    protocol
    Qt5::Core
)
