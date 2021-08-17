set(SUBDIR_NAME protocoltool_common)

file(GLOB_RECURSE SOURCE_GLOB_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp" "*.h")

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Communication
)
add_library(${SUBDIR_NAME} STATIC ${SOURCE_GLOB_FILES})

target_link_libraries(${SUBDIR_NAME}
PUBLIC
    Communication
    Qt5::Core
    Qt5::SerialPort
    Qt5::Concurrent
)