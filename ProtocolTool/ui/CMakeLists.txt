set(SUBDIR_NAME protocoltool_ui)
set(CMAKE_AUTOUIC ON)

file(GLOB_RECURSE SOURCE_GLOB_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.h")
file(GLOB_RECURSE UI_GLOB_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.ui")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Communication
    ${CMAKE_CURRENT_SOURCE_DIR}/../common
    ${CMAKE_CURRENT_SOURCE_DIR}/../protocol
)

add_library(${SUBDIR_NAME}
STATIC
    ${SOURCE_GLOB_FILES}
    ${UI_GLOB_FILES}
)

target_link_libraries(${SUBDIR_NAME}
PUBLIC
    Communication
    protocoltool_common
    protocoltool_protocol
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    Qt5::SerialPort
)