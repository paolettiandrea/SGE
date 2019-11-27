target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        EngineCore.hpp
        EngineCore.cpp
        )

add_subdirectory(subsystems)
add_subdirectory(debug)


