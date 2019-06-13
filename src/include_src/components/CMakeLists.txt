target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        IComponent.cpp

        LogicHub.cpp
        Transform.cpp

        PathRenderer.cpp
        VertArray.cpp

        Rigidbody.cpp
        BoxCollider.cpp
        CircleCollider.cpp
        )