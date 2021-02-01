add_library(ut "")

target_sources(ut
PRIVATE
    cdtexut.cpp
    utmintorstrategy.cpp
    utwfstrategy.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/cdtexut.h
    ${CMAKE_CURRENT_LIST_DIR}/utmintorstrategy.h
    ${CMAKE_CURRENT_LIST_DIR}/utwfstrategy.h
)

target_include_directories(ut PUBLIC ${CMAKE_CURRENT_LIST_DIR})