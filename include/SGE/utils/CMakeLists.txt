target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PUBLIC
        Matrix2D.hpp
        )

add_subdirectory(log)
add_subdirectory(terminal)
add_subdirectory(time)
add_subdirectory(handles)
add_subdirectory(events)