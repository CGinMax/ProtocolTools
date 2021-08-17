set(SUBDIR_NAME protocoltool_protocol)

file(GLOB_RECURSE SOURCE_GLOB_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.h")

set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Communication
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
)

add_library(${SUBDIR_NAME}
STATIC
    ${SOURCE_GLOB_FILES}
)

target_link_libraries(${SUBDIR_NAME}
PUBLIC
    Communication
    protocoltool_common
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
)
