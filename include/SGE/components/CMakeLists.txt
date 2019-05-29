target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        IComponent.hpp
        Component.hpp

        Transform.hpp
        LogicHub.hpp
        )

add_subdirectory(graphics)
add_subdirectory(physics)