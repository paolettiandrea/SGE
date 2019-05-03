target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        Subsystem.cpp
        Subsystem.hpp)

add_subdirectory(object-manager)
add_subdirectory(logic-manager)
add_subdirectory(window-manager)