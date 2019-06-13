cmake_minimum_required(VERSION 3.13)
project(SGE)

set(CMAKE_CXX_STANDARD 17)

add_library(SGE STATIC)

add_executable(tester tester/main.cpp tester/BoxSpawner.cpp tester/BoxSpawner.hpp tester/PhysicsBox.cpp tester/PhysicsBox.hpp tester/Wiggler.hpp tester/TestLogic.hpp tester/TestLogic.cpp tester/PhysicsCircle.cpp tester/PhysicsCircle.hpp tester/Box.hpp)
target_link_libraries(tester PUBLIC SGE)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(SGE PUBLIC DEBUG=1)

else()
    target_compile_definitions(SGE PUBLIC RELEASE=1)
endif()



add_subdirectory(src)
add_subdirectory(include)
add_subdirectory(resources)



SET(BOX2D_BUILD_EXAMPLES OFF CACHE BOOL "This setting has been overridden" FORCE)
SET(BOX2D_BUILD_SHARED OFF CACHE BOOL "This setting has been overridden" FORCE)
SET(BOX2D_INSTALL OFF CACHE BOOL "This setting has been overridden" FORCE)

add_subdirectory(lib/Box2D/Box2D)
target_link_libraries(SGE PUBLIC Box2D)
target_include_directories(SGE PUBLIC
        lib/Box2D/Box2D
        )


SET(BUILD_SHARED_LIBS OFF CACHE BOOL "This setting has been overridden" FORCE)
SET(SFML_BUILD_EXAMPLES OFF CACHE BOOL "This setting has been overridden" FORCE)
SET(SFML_BUILD_TEST_SUITE OFF CACHE BOOL "This setting has been overridden" FORCE)
SET(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "This setting has been overridden" FORCE)
if (MINGW)
    SET(SFML_USE_STATIC_STD_LIBS ON CACHE BOOL "This setting has been overridden" FORCE)
endif()

add_compile_definitions(SFML_STATIC)
target_include_directories(SGE PUBLIC
        lib/SFML/include
        )
add_subdirectory(lib/SFML)

target_link_libraries(SGE PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
        )

if(MINGW)
    target_link_libraries(SGE PUBLIC
            sfml-main
            )
endif()






