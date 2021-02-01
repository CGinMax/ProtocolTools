add_library(nr "")

target_sources(nr
PRIVATE
    cdtexnr.cpp
    nrmintorstrategy.cpp
    nrwfstrategy.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/cdtexnr.h
    ${CMAKE_CURRENT_LIST_DIR}/nrmintorstrategy.h
    ${CMAKE_CURRENT_LIST_DIR}/nrwfstrategy.h
)

target_include_directories(nr PUBLIC ${CMAKE_CURRENT_LIST_DIR})