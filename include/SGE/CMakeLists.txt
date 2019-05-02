target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        engine/Engine.hpp
        GameObject.hpp
        Scene.hpp
        SceneConstructionData.hpp
        )

add_subdirectory(engine)
add_subdirectory(components)
add_subdirectory(logic)
add_subdirectory(utils)