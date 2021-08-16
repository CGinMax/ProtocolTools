
set(SUBDIR_NAME pressplatetool_common)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Network
    SerialPort
    Concurrent
)

set(CMAKE_AUTOMOC ON)

file(GLOB SUBDIR_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")

add_library(${SUBDIR_NAME}
STATIC
    ${SUBDIR_SOURCES}
)

target_link_libraries(${SUBDIR_NAME} PUBLIC
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
    Qt5::Concurrent
)
