target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        Engine.cpp

        GameObject.cpp
        Scene.cpp

        Logic.cpp

        Vec2.cpp

        Camera.cpp
        )

add_subdirectory(utils)
add_subdirectory(debug)
add_subdirectory(components)