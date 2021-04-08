aux_source_directory(. UT_SRC_DIR)
add_library(ut STATIC ${UT_SRC_DIR})

target_include_directories(ut PUBLIC ..)
target_include_directories(ut PUBLIC ../standard)

target_link_libraries(ut PUBLIC Qt5::Core)

# target_sources(ut
# PRIVATE
#     cdtexut.cpp
#     utmintorstrategy.cpp
#     utwfstrategy.cpp
# PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/cdtexut.h
#     ${CMAKE_CURRENT_LIST_DIR}/utmintorstrategy.h
#     ${CMAKE_CURRENT_LIST_DIR}/utwfstrategy.h
# )

# target_include_directories(ut PUBLIC ${CMAKE_CURRENT_LIST_DIR})