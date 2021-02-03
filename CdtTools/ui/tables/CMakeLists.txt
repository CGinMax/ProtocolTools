aux_source_directory(. TBALES_SRC_DIR)
aux_source_directory(./delegates TBALES_SRC_DIR)

add_library(tables STATIC ${TBALES_SRC_DIR})

target_link_libraries(tables
PUBLIC
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)