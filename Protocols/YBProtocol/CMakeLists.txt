
add_subdirectory(content)

add_library(YBProtocol STATIC
ybframe.h
ybframeenums.h
ybprotocol.h
ybprotocolexception.h
ybframe.cpp
ybprotocol.cpp
ybprotocolexception.cpp
)

target_link_libraries(YBProtocol PUBLIC content)
