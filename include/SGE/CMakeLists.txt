target_include_directories(SGE PRIVATE .)

target_sources(SGE PUBLIC
        engine/Engine.hpp
        GameObject.hpp
        Scene.hpp
        Scene_ConstructionData.hpp
        Vec2.hpp
        Camera.hpp
        Path.hpp
        )

add_subdirectory(engine)
add_subdirectory(components)
add_subdirectory(logic)
add_subdirectory(utils)