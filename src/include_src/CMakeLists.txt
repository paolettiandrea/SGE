target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        GameObject.cpp
        Scene.cpp

        Component.cpp
        LogicHub.cpp
        Transform.cpp
        Path.cpp

        Logic.cpp

        Engine.cpp
        )

add_subdirectory(utils)