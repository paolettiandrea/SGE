target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        Factory.hpp
        Factory.cpp

        gameobjects/GameObjectMemoryLayer.cpp
        gameobjects/GameObjectMemoryLayer.hpp)

add_subdirectory(components)