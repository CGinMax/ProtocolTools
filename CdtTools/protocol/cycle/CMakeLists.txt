add_library(cycle "")

target_sources(cycle 
PRIVATE
    cdtstandard.cpp
    standardmintorstrategy.cpp
    standardwfstrategy.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/cdtstandard.h
    ${CMAKE_CURRENT_LIST_DIR}/standardmintorstrategy.h
    ${CMAKE_CURRENT_LIST_DIR}/standardwfstrategy.h
)

target_include_directories(cycle PUBLIC ${CMAKE_CURRENT_LIST_DIR})