
set(SUBDIR_NAME protocol)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Communication)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../asyncfuture)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../../Protocols)

add_library(${SUBDIR_NAME}
    STATIC
    protocolchannelbase.h
    protocolchannelbase.cpp
    ybprotocolchannel.h
    ybprotocolchannel.cpp
)

target_link_libraries(${SUBDIR_NAME}
PUBLIC
#    asyncfuture
    Protocols
    Communication
    Qt5::Core
)
