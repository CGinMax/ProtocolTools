
set(SUBDIR_NAME pressplatetool_protocol)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

set(CMAKE_AUTOMOC ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Communication)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../asyncfuture)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Protocols)

file(GLOB SUBDIR_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
add_library(${SUBDIR_NAME}
    STATIC
    ${SUBDIR_SOURCES}
)

target_link_libraries(${SUBDIR_NAME}
PUBLIC
    qtasyncfuture
    Protocols
    Communication
    Qt5::Core
)
