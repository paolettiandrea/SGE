target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        EngineCoreDebug.hpp
        EngineCoreDebug.cpp
        )

add_subdirectory(hierarchy_panel)
add_subdirectory(profiler)
add_subdirectory(fps-counter)