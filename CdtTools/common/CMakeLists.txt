set(COMMON_SRC
    workerthread.h
    workerthread.cpp
    threadpool.h
    threadpool.cpp
    util.h
    util.cpp
)

add_library(common STATIC ${COMMON_SRC})
target_link_libraries(common PUBLIC Qt::Core Qt::Concurrent)