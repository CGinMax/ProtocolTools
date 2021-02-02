aux_source_directory(. PROTOCOL_SRC_DIR)
add_library(protocol ${PROTOCOL_SRC_DIR})

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

target_include_directories(protocol PUBLIC ../network)
target_include_directories(protocol PUBLIC ../ui)
target_link_libraries(protocol PUBLIC Qt::Core)
target_link_libraries(protocol
PRIVATE
    standard
    cycle
    interacte
    nr
    ut
)