aux_source_directory(. NR_SRC_DIR)
add_library(nr STATIC ${NR_SRC_DIR})

target_include_directories(nr PUBLIC ..)
target_include_directories(nr PUBLIC ../standard)

target_link_libraries(nr PUBLIC Qt5::Core Qt5::SerialPort)

# target_sources(nr
# PRIVATE
#     cdtexnr.cpp
#     nrmintorstrategy.cpp
#     nrwfstrategy.cpp
# PUBLIC
#     ${CMAKE_CURRENT_LIST_DIR}/cdtexnr.h
#     ${CMAKE_CURRENT_LIST_DIR}/nrmintorstrategy.h
#     ${CMAKE_CURRENT_LIST_DIR}/nrwfstrategy.h
# )

# target_include_directories(nr PUBLIC ${CMAKE_CURRENT_LIST_DIR})