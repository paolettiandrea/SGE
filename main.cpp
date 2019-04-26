#include <iostream>
#include <SGE/components/LogicHub.hpp>
#include "Factory.hpp"
#include "include/SGE/Scene.hpp"

#include "ComponentMemoryLayer.hpp"
#include "Transform.hpp"
#include "ComponentFactory.hpp"
#include "components/component_creators/ComponentCreator.hpp"

int main() {
    std::cout << "Hello, World!" << std::endl;
    Factory factory;


    ComponentCreator<Transform> transform_creator ("Transform");
    ComponentCreator<LogicHub> logic_creator ("LogicHub");


    Scene* scene = factory.push_new_scene();


    Handle<GameObject> go1 = scene->spawn_gameobject("Test Object 1");
    Handle<GameObject> go2 = scene->spawn_gameobject("Test Object 2");
    Handle<GameObject> go3 = scene->spawn_gameobject("Test Object 3");
    Handle<GameObject> go4 = scene->spawn_gameobject("Test Object 4");
    Handle<GameObject> go5 = scene->spawn_gameobject("Test Object 5");

    auto trans1 = go1->add_component<Transform>("Transform");
    auto trans2 = go2->add_component<Transform>("Transform");
    auto trans3 = go3->add_component<Transform>("Transform");
    auto trans4 = go4->add_component<Transform>("Transform");


    go1->add_component<LogicHub>("LogicHub");


    go1->remove_component("Transform");
    go2->remove_component("Transform");


    return 0;
}