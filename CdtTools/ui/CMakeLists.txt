aux_source_directory(. UI_SRC_DIR)
aux_source_directory(./dialog UI_SRC_DIR)

add_library(ui STATIC ${UI_SRC_DIR})

# add_subdirectory(dialog)
add_subdirectory(tables)
add_subdirectory(tabs)

target_include_directories(ui PUBLIC tables ../network)
target_link_libraries(ui
PUBLIC
    # dialog
    tables
    tabs
    network
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)