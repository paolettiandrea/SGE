target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        Factory.hpp
        Factory.cpp)

add_subdirectory(components)
add_subdirectory(gameobjects)