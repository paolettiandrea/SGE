cmake_minimum_required(VERSION 3.13)
project(factory_experiments)

set(CMAKE_CXX_STANDARD 17)

add_library(factory_experiments)

add_executable(tester tester/main.cpp tester/WigglerSpawner.cpp tester/WigglerSpawner.hpp tester/LogBehaviour.cpp tester/LogBehaviour.hpp tester/Wiggler.hpp tester/HierarchyTestLogic.hpp tester/TestTransform.cpp tester/TestTransform.hpp tester/Matrix2D.hpp)
target_link_libraries(tester PUBLIC factory_experiments)



if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(factory_experiments PUBLIC DEBUG=1)

else()
    target_compile_definitions(factory_experiments PUBLIC RELEASE=1)
endif()



add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(resources)



target_link_libraries(factory_experiments PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.5.1/lib/libsfml-audio.so.2.5.1
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.5.1/lib/libsfml-graphics.so.2.5.1
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.5.1/lib/libsfml-window.so.2.5.1
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.5.1/lib/libsfml-network.so.2.5.1
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-2.5.1/lib/libsfml-system.so.2.5.1)

target_include_directories(factory_experiments PUBLIC
        lib/SFML-2.5.1/include
        )


