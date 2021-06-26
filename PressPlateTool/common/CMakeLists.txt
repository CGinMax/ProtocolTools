# PPT: PressPlateTool
set(SUBDIR_NAME common)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Network
    SerialPort
    Concurrent
)


add_library(${SUBDIR_NAME}
    STATIC

    threadpool.h
    threadpool.cpp
    workerthread.h
    workerthread.cpp
)

target_link_libraries(${SUBDIR_NAME} PUBLIC
    Qt5::Core
    Qt5::Network
    Qt5::SerialPort
    Qt5::Concurrent
)
