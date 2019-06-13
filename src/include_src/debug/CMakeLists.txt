target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        DebugShape.cpp
        PointDebugShape.cpp
        LineDebugShape.cpp
        )