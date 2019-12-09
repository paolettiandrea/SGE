target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        IComponent.cpp

        LogicHub.cpp
        Transform.cpp

        VertArray.cpp

        Rigidbody.cpp
        Collider.cpp
        CollisionInfo.cpp

        UI.cpp
        UIContent.cpp
        UIText.cpp
        UIBar.cpp
        )