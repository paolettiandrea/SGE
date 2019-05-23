target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        IComponent.hpp
        Transform.hpp
        LogicHub.hpp
        Polygon.hpp
        Component.hpp
        )

add_subdirectory(graphics)