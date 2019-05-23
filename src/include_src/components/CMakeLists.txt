target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        IComponent.cpp

        LogicHub.cpp
        Transform.cpp

        GraphicsComponent.cpp
        VertArray.cpp
        )