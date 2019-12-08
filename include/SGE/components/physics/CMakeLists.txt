target_include_directories(SGE PRIVATE .)

target_sources(SGE PUBLIC
        Rigidbody.hpp
        Collider.hpp

        CollisionInfo.hpp
        PhysicsMaterial.hpp
        )