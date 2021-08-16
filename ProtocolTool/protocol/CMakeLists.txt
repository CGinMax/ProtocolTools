set(SUBDIR_NAME protocoltools_protocol)
aux_source_directory(. PROTOCOL_SRC_DIR)
add_library(${SUBDIR_NAME} ${PROTOCOL_SRC_DIR})

# target_sources(protocol
# PRIVATE
#     cdtframe.cpp
#     checkhelper.cpp
#     protocolbase.cpp
#     strategybase.cpp
# PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/cdtframe.h
#     ${CMAKE_CURRENT_LIST_DIR}/checkhelper.h
#     ${CMAKE_CURRENT_LIST_DIR}/protocolbase.h
#     ${CMAKE_CURRENT_LIST_DIR}/strategybase.h
# )
# target_include_directories(protocol PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(standard)
add_subdirectory(cycle)
add_subdirectory(interacte)
add_subdirectory(nr)
add_subdirectory(ut)

target_include_directories(${SUBDIR_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../ui)
target_link_libraries(${SUBDIR_NAME} PUBLIC Qt5::Core Qt5::SerialPort)
target_link_libraries(${SUBDIR_NAME}
PRIVATE
    standard
    cycle
    interacte
    nr
    ut
)