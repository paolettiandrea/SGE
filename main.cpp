#include <iostream>
#include <SGE/components/LogicHub.hpp>
#include "Factory.hpp"
#include "include/SGE/Scene.hpp"

#include "ComponentMemoryLayer.hpp"
#include "Transform.hpp"
#include "ComponentFactory.hpp"
#include "components/component_creators/ComponentCreator.hpp"

#include "DummyLogic.hpp"

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



    auto logic_hub = go1->get_component<LogicHub>("LogicHub");
    logic_hub->attach_logic(new DummyLogic);
    DummyLogic* lo = logic_hub->get_logic<DummyLogic>("DummyLogic");

    Handle<LogicHub> hub = go1->get_component<LogicHub>("LogicHub");





    return 0;
}