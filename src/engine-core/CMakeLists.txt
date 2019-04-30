target_include_directories(factory_experiments PRIVATE .)

target_sources(factory_experiments PRIVATE
        EngineCore.hpp
        EngineCore.cpp)

add_subdirectory(subsystems)


