add_executable(tester main.cpp)

target_include_directories(factory_experiments PUBLIC .)


target_link_libraries(tester factory_experiments)