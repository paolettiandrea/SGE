target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        ComponentFactory.hpp
        ComponentFactory.cpp)


add_subdirectory(component_creators)
add_subdirectory(component_memory_layers)