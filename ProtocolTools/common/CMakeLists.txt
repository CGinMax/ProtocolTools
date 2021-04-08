set(COMMON_SRC
    workerthread.h
    workerthread.cpp
    threadpool.h
    threadpool.cpp
    util.h
    util.cpp
)

add_library(common STATIC ${COMMON_SRC})
target_link_libraries(common PUBLIC Qt5::Core Qt5::Concurrent)