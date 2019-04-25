target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        GameObject.cpp
        Scene.cpp

        Component.cpp
        LogicHub.cpp
        Transform.cpp
        )