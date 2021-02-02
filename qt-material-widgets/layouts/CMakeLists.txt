aux_source_directory(. LAYOUTS_SRC)
add_library(layouts OBJECT ${LAYOUTS_SRC})

target_link_libraries(layouts PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)