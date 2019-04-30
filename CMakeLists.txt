cmake_minimum_required(VERSION 3.13)
project(factory_experiments)

set(CMAKE_CXX_STANDARD 17)

add_library(factory_experiments)

add_subdirectory(tester)





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


