aux_source_directory(. LIB_SRC)
add_library(lib OBJECT ${LIB_SRC})

target_include_directories(lib PUBLIC ..)
target_link_libraries(lib PUBLIC Qt5::Core Qt5::Gui Qt5::Widgets)