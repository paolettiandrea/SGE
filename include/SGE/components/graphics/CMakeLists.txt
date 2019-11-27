target_include_directories(SGE PRIVATE .)

target_sources(SGE PUBLIC
        VertArray.hpp
        PathRenderer.hpp
        )

add_subdirectory(ui)