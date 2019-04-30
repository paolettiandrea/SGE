target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        Engine.hpp
        GameObject.hpp
        Scene.hpp
        )

add_subdirectory(components)
add_subdirectory(logic)
add_subdirectory(utils)