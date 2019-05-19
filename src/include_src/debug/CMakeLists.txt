target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        DebugShape.cpp
        PointDebugShape.cpp
        LineDebugShape.cpp
        )