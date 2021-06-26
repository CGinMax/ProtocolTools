# PressPlateTool
set(SUBDIR_NAME model)

find_package(Qt5 REQUIRED COMPONENTS
    Core
)

include_directories(../../Communication)
add_library(${SUBDIR_NAME}
STATIC
    gatherdata.h
    gatherdata.cpp
    ybsensordata.h
    ybsensordata.cpp
    gatherconfiguremodel.h
    gatherconfiguremodel.cpp
)


target_link_libraries(${SUBDIR_NAME}
PUBLIC
    Communication
    Qt5::Core
)
