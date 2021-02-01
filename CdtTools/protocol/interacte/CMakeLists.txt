add_library(interacte "")

target_sources(interacte
PRIVATE
    cdtinteracte.cpp
    intermintorstrategy.cpp
    interwfstrategy.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/cdtinteracte.h
    ${CMAKE_CURRENT_LIST_DIR}/intermintorstrategy.h
    ${CMAKE_CURRENT_LIST_DIR}/interwfstrategy.h
)

target_include_directories(interacte PUBLIC ${CMAKE_CURRENT_LIST_DIR})