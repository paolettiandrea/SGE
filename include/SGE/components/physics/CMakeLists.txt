target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        Rigidbody.hpp

        Collider.hpp
        BoxCollider.hpp
        CircleCollider.hpp
        )