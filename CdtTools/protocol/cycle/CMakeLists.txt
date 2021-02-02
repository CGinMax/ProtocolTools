aux_source_directory(. CYCLE_SRC_DIR)
add_library(cycle ${CYCLE_SRC_DIR})

target_include_directories(cycle PUBLIC ..)
target_include_directories(cycle PUBLIC ../standard)

target_link_directories(cycle PUBLIC Qt::Core)
# target_sources(cycle 
# PRIVATE
#     cdtstandard.cpp
#     standardmintorstrategy.cpp
#     standardwfstrategy.cpp
# PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/cdtstandard.h
#     ${CMAKE_CURRENT_LIST_DIR}/standardmintorstrategy.h
#     ${CMAKE_CURRENT_LIST_DIR}/standardwfstrategy.h
# )

# target_include_directories(cycle PUBLIC ${CMAKE_CURRENT_LIST_DIR})