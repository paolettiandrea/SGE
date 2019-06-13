target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        Engine.cpp

        GameObject.cpp
        Scene.cpp

        Logic.cpp

        Vec2.cpp

        Camera.cpp

        Path.cpp
        )

add_subdirectory(utils)
add_subdirectory(debug)
add_subdirectory(components)