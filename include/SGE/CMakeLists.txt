target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        GameObject.hpp
        Scene.hpp
        )

add_subdirectory(components)
add_subdirectory(utils)
add_subdirectory(misc)