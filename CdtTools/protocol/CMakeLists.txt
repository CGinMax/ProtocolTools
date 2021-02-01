add_library(protocol)

add_subdirectory(standard)
add_subdirectory(cycle)
add_subdirectory(interacte)
add_subdirectory(nr)
add_subdirectory(ut)

target_link_libraries(protocol
    standard
    cycle
    interacte
    nr
    ut
    )