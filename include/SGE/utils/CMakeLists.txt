target_include_directories(SGE PRIVATE .)

target_sources(SGE PUBLIC
        Matrix2D.hpp
        )

add_subdirectory(log)
add_subdirectory(terminal)
add_subdirectory(time)
add_subdirectory(handles)
add_subdirectory(events)