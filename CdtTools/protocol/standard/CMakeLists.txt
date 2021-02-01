add_library(standard "")

target_sources(standard
PRIVATE
    cdtprotocol.cpp
    cdtmintorstrategy.cpp
    cdtwfstrategy.cpp
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/cdtprotocol.h
    ${CMAKE_CURRENT_LIST_DIR}/cdtmintorstrategy.h
    ${CMAKE_CURRENT_LIST_DIR}/cdtwfstrategy.h
)

target_include_directories(standard PUBLIC ${CMAKE_CURRENT_LIST_DIR})