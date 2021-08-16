add_library(interacte "")


# include_directories(..)
# include_directories(../standard)

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
target_include_directories(interacte PUBLIC ..)
target_include_directories(interacte PUBLIC ../standard)
target_link_libraries(interacte PUBLIC Qt5::Core Qt5::SerialPort)