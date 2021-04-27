set(NETWORK_SRC
    networkbase.h
    networkbase.cpp
    tcpclient.h
    tcpclient.cpp
    tcpserver.h
    tcpserver.cpp
)

add_library(network STATIC ${NETWORK_SRC})
target_link_libraries(network PUBLIC Qt5::Core Qt5::Network)