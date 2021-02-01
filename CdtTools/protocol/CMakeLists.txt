add_library(protocol "")

target_sources(protocol
PRIVATE
    cdtframe.cpp
    checkhelper.cpp
    protocolbase.cpp
    strategybase.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/cdtframe.h
    ${CMAKE_CURRENT_LIST_DIR}/checkhelper.h
    ${CMAKE_CURRENT_LIST_DIR}/protocolbase.h
    ${CMAKE_CURRENT_LIST_DIR}/strategybase.h
)
target_include_directories(protocol PUBLIC ${CMAKE_CURRENT_LIST_DIR})
add_subdirectory(standard)
add_subdirectory(cycle)
add_subdirectory(interacte)
add_subdirectory(nr)
add_subdirectory(ut)

target_link_libraries(protocol
PUBLIC
    standard
    cycle
    interacte
    nr
    ut
)