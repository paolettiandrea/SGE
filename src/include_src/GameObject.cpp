#include "GameObject.hpp"

#include <iostream>
#include "ComponentFactory.hpp"
#include "IComponentMemoryLayer.hpp"
#include "Scene.hpp"


GameObject::GameObject(Scene* _scene, const std::string& _name)
    : scene(_scene)
    , name(_name)
    , handle(this){
    std::cout << "Construction of GameObject " << name << std::endl;

    for (int &val : my_components_mapped_array) {
        val = -1;
    }
}

GameObject::~GameObject() {
    std::cout << "Destruction of GameObject " << name << std::endl;

}

Handle<GameObject> &GameObject::get_handle() {
    return handle;
}

bool GameObject::has_component(const std::string &id) {
    return (my_components_mapped_array[ComponentFactory::id_to_index(id)] != -1);
}

void GameObject::remove_component(const std::string &id) {
    unsigned int type_index = ComponentFactory::id_to_index(id);
    int comp_index = my_components_mapped_array[type_index];
    if (comp_index >= 0) {
        scene->get_component_memorylayer_array()[type_index]->remove_unspecified_component(comp_index);
        my_components_mapped_array[type_index] = -1;
    } else {
        std::cout << "Error: Tried to remove an inexistent component with id [" << id << "]" << std::endl;
        exit(1);
    }
}

unsigned int GameObject::add_unspecified_component(const std::string &id) {
    unsigned int type_index = ComponentFactory::id_to_index(id);
    auto yo = scene->get_component_memorylayer_array();
    my_components_mapped_array[type_index] = yo[type_index]->create_unspecified_component(this->get_handle());
    return my_components_mapped_array[type_index];
}

unsigned int GameObject::id_to_index(const std::string &id) {
    return ComponentFactory::id_to_index(id);
}









