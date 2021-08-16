aux_source_directory(. TBAS_SRC_DIR)

add_library(tabs STATIC ${TBAS_SRC_DIR})

target_link_libraries(tabs
PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
    Qt5::Network
    Qt5::SerialPort
)