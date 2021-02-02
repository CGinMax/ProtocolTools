aux_source_directory(. UI_SRC_DIR)
add_library(ui ${UI_SRC_DIR})

add_subdirectory(dialog)
add_subdirectory(tables)
add_subdirectory(tabs)

target_link_libraries(ui
PRIVATE
    dialog
    tables
    tabs
)