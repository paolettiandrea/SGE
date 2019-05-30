cmake_minimum_required(VERSION 3.13)
project(factory_experiments)

set(CMAKE_CXX_STANDARD 17)

add_library(factory_experiments)

add_executable(tester tester/main.cpp tester/BoxSpawner.cpp tester/BoxSpawner.hpp tester/PhysicsBox.cpp tester/PhysicsBox.hpp tester/Wiggler.hpp tester/TestLogic.hpp tester/TestLogic.cpp)
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



SET(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "This setting has been overridden")
SET(BOX2D_BUILD_SHARED OFF CACHE BOOL "This setting has been overridden")
SET(BOX2D_INSTALL OFF CACHE BOOL "This setting has been overridden")

add_subdirectory(lib/Box2D/Box2D)
target_link_libraries(factory_experiments PUBLIC Box2D)
target_include_directories(factory_experiments PUBLIC
        lib/Box2D/Box2D
        )


SET(BUILD_SHARED_LIBS OFF CACHE BOOL "This setting has been overridden")
SET(SFML_BUILD_EXAMPLES OFF CACHE BOOL "This setting has been overridden")
SET(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "This setting has been overridden")
SET(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "This setting has been overridden")

add_compile_definitions(SFML_STATIC)
add_subdirectory(lib/SFML)
if(UNIX)
target_link_libraries(factory_experiments PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
        sfml-network
        )
elseif(MINGW)
    target_link_libraries(factory_experiments PUBLIC
            sfml-graphics
            sfml-window
            sfml-system
            sfml-main
            )
endif()

target_include_directories(factory_experiments PUBLIC
        lib/SFML/include
        )




