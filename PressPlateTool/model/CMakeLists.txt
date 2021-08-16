# PressPlateTool
set(SUBDIR_NAME pressplatetool_model)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

set(CMAKE_AUTOMOC ON)

include_directories(../../Communication)

file(GLOB SUBDIR_SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
add_library(${SUBDIR_NAME}
STATIC
    ${SUBDIR_SOURCES}
)


target_link_libraries(${SUBDIR_NAME}
PUBLIC
    Communication
    Qt5::Core
)
