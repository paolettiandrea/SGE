target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        ObjectManager.hpp
        ObjectManager.cpp)

add_subdirectory(components)
add_subdirectory(gameobjects)