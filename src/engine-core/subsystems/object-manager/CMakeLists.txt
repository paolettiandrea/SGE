target_include_directories(SGE PRIVATE .)

target_sources(SGE PRIVATE
        ObjectManager.hpp
        ObjectManager.cpp)

add_subdirectory(components)
add_subdirectory(gameobjects)