target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        Subsystem.cpp
        Subsystem.hpp)

add_subdirectory(object-manager)
add_subdirectory(logic-manager)
add_subdirectory(window-manager)
add_subdirectory(physics-manager)