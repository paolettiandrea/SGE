target_include_directories(SGE PRIVATE .)

target_sources(SGE PUBLIC
        Engine.hpp
        IEnvironment.hpp
        )

add_subdirectory(construction_data)