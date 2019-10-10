target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        PhysicsManager.cpp
        PhysicsManager.hpp

        CustomB2ContactListener.cpp
        CustomB2ContactListener.hpp
        )
