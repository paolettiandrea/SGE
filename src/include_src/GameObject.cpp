#include "GameObject.hpp"

#include <iostream>
#include "ComponentFactory.hpp"
#include "IComponentMemoryLayer.hpp"
#include "Scene.hpp"


GameObject::GameObject(Scene* _scene, const std::string& _name)
    : Loggable("{" + _name + "}")
    , scene(_scene)
    , gameobject_handle(this)
    {
    LOG_DEBUG(19) << "Construction";

    for (int &val : my_components_mapped_array) {
        val = -1;
    }

    transform_handle = add_component<Transform>("Transform");
    logichub_handle = add_component<LogicHub>("LogicHub");
}

GameObject::~GameObject() {
    LOG_DEBUG(19) << "Destruction";

}

Handle<GameObject> &GameObject::get_handle() {
    return gameobject_handle;
}

bool GameObject::has_component(const std::string &id) {
    return (my_components_mapped_array[ComponentFactory::id_to_index(id)] != -1);
}

void GameObject::remove_component(const std::string &id) {

    LOG_DEBUG(19) << "Removing component of id [" + id + "]";
    if (id == "Transform" || id == "LogicHub") {
        LOG_ERROR << "It's not possible to remove Transform or LogicHub components";
        exit(1);
    }

    unsigned int type_index = ComponentFactory::id_to_index(id);
    int comp_index = my_components_mapped_array[type_index];
    if (comp_index >= 0) {
        scene->get_component_memorylayer_array()[type_index]->remove_unspecified_component(comp_index);
        my_components_mapped_array[type_index] = -1;

    } else {
        LOG_ERROR << "Error: Tried to remove an inexistent component with id [" << id << "]";
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

const Handle<Transform> &GameObject::transform() const {
    return transform_handle;
}

 Handle<LogicHub> &GameObject::logichub() {
    return logichub_handle;
}









