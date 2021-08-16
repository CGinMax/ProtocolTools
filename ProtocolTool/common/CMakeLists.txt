
set(SUBDIR_NAME protocoltools_common)
set(COMMON_SRC
    workerthread.h
    workerthread.cpp
    threadpool.h
    threadpool.cpp
    util.h
    util.cpp
)

add_library(${SUBDIR_NAME} STATIC ${COMMON_SRC})
target_link_libraries(${SUBDIR_NAME} PUBLIC Qt5::Core Qt5::SerialPort Qt5::Concurrent)