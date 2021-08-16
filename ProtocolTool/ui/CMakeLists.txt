set(SUBDIR_NAME protocoltools_ui)
aux_source_directory(. UI_SRC_DIR)
message("UI SRC DIR:${UI_SRC_DIR}")
aux_source_directory(./dialog UI_SRC_DIR)

add_library(${SUBDIR_NAME} STATIC ${UI_SRC_DIR})

# add_subdirectory(dialog)
add_subdirectory(tables)
add_subdirectory(tabs)

target_include_directories(${SUBDIR_NAME} PUBLIC tables )
target_link_libraries(${SUBDIR_NAME}
PUBLIC
    # dialog
    tables
    tabs
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
    Qt5::SerialPort
)