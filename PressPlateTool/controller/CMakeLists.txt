set(SUBDIR_NAME pressplatetool_controller)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

set(CMAKE_AUTOMOC ON)

include_directories(../../Communication)
include_directories(../model)
include_directories(../common)
include_directories(../protocol)

file(GLOB SUBDIR_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
add_library(${SUBDIR_NAME}
STATIC
    ${SUBDIR_SOURCES}
)

target_link_libraries(${SUBDIR_NAME}
PUBLIC
    Communication
    Protocols
    pressplatetool_common
    pressplatetool_model
    pressplatetool_protocol
    Qt5::Core
)
