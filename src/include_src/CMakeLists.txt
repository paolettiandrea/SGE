target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        Engine.cpp

        GameObject.cpp
        Scene.cpp

        IComponent.cpp
        LogicHub.cpp
        Transform.cpp
        Polygon.cpp

        Logic.cpp

        Vec2.cpp
        )

add_subdirectory(utils)