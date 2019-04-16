#include <iostream>
#include "Factory.hpp"
#include "Scene.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Factory factory;
    factory.build_scene();

    factory.get_top_scene()->destroy_gameobject(factory.get_top_scene()->spawn_gameobject("GO"));
    Handle<GameObject>::print_entries_array_info();

    return 0;
}