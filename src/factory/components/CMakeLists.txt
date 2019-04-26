target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        ComponentFactory.hpp
        ComponentFactory.cpp)


add_subdirectory(component_creators)
add_subdirectory(component_memory_layers)