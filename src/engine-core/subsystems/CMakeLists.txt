target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        Subsystem.cpp
        Subsystem.hpp)

add_subdirectory(scene-manager)
add_subdirectory(logic-subsystem)