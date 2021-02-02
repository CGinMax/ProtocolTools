aux_source_directory(. STANDARD_SRC_DIR)
add_library(standard STATIC ${STANDARD_SRC_DIR})

target_include_directories(standard PUBLIC ..)

target_link_libraries(standard PUBLIC Qt::Core)

# target_sources(standard
# PRIVATE
#     cdtprotocol.cpp
#     cdtmintorstrategy.cpp
#     cdtwfstrategy.cpp
# PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/cdtprotocol.h
#     ${CMAKE_CURRENT_LIST_DIR}/cdtmintorstrategy.h
#     ${CMAKE_CURRENT_LIST_DIR}/cdtwfstrategy.h
# )

# target_include_directories(standard PUBLIC ${CMAKE_CURRENT_LIST_DIR})