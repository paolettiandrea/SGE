target_include_directories(SGE PRIVATE .)

target_sources(SGE PUBLIC
        IComponent.hpp
        Component.hpp

        Transform.hpp
        LogicHub.hpp
        )

add_subdirectory(graphics)
add_subdirectory(physics)