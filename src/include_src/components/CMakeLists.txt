target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        IComponent.cpp

        LogicHub.cpp
        Transform.cpp

        PathRenderer.cpp
        VertArray.cpp

        Rigidbody.cpp
        BoxCollider.cpp
        CircleCollider.cpp
        )