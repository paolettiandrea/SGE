#include <iostream>
#include "Factory.hpp"
#include "include/SGE/Scene.hpp"

#include "ComponentArray.hpp"
#include "Transform.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Factory factory;
    factory.build_scene();

    Handle<GameObject> go1 = factory.get_top_scene()->spawn_gameobject("GO1");
    Handle<GameObject> go2 = factory.get_top_scene()->spawn_gameobject("GO2");
    Handle<GameObject> go3 = factory.get_top_scene()->spawn_gameobject("GO3");
    Handle<GameObject> go4 = factory.get_top_scene()->spawn_gameobject("GO4");

    ComponentArray<Transform> transform_array;
    Handle<Transform> trans1 = transform_array.create_new_component(go1);
    Handle<Transform> trans2 = transform_array.create_new_component(go2);
    Handle<Transform> trans3 = transform_array.create_new_component(go3);
    Handle<Transform> trans4 = transform_array.create_new_component(go4);
    Handle<Transform>::print_entries_array_info();

    transform_array.remove_component(trans2);
    transform_array.remove_component(trans1);

    transform_array.create_new_component(go1);
    transform_array.create_new_component(go1);



    Handle<Transform>::print_entries_array_info();


    Handle<GameObject> yo = trans4->gameobject();
    std::cout << yo->name << std::endl;





    return 0;
}