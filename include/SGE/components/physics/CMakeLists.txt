target_include_directories(SGE PRIVATE .)

target_sources(SGE PUBLIC
        Rigidbody.hpp

        ICollider.hpp
        Collider.hpp
        BoxCollider.hpp
        CircleCollider.hpp
        PolygonCollider.hpp
        )