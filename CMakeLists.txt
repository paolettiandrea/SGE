cmake_minimum_required(VERSION 3.13)
project(factory_experiments)

set(CMAKE_CXX_STANDARD 17)

add_executable(factory_experiments main.cpp
        Scene.hpp
        Scene.cpp

        GameObject.hpp
        GameObject.cpp

        Component.cpp
        Component.hpp)

add_subdirectory(factory)
add_subdirectory(handles)