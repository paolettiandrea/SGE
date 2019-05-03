#include "SGE/GameObject.hpp"

#include <iostream>
#include "ComponentFactory.hpp"
#include "IComponentMemoryLayer.hpp"
#include "Scene.hpp"
#include "Logic.hpp"

using namespace sge;
using namespace sge::core;
using utils::Handle;

GameObject::GameObject(Scene* _scene, const std::string& _name)
    : Loggable("{" + _name + "}")
    , m_scene(_scene)
    , gameobject_handle(this)
    {
    LOG_DEBUG(19) << "Construction";

    for (int &val : m_components_mapped_array) {
        val = -1;
    }

    transform_handle = add_component<Transform>("Transform");
    logichub_handle = add_component<LogicHub>("LogicHub");
}

GameObject::~GameObject() {
    LOG_DEBUG(19) << "Destruction";

}

void GameObject::doom() {
    LOG_DEBUG(32) << "Doomed";
    is_doomed_flag = true;
}


Handle<GameObject> GameObject::get_handle() {
    return gameobject_handle;
}

void GameObject::swap(GameObject& other_gameobj) {
    for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
        auto temp = m_components_mapped_array[i];
        m_components_mapped_array[i] = other_gameobj.m_components_mapped_array[i];
        other_gameobj.m_components_mapped_array[i] = temp;
    }

    bool temp_flag = is_doomed_flag;
    is_doomed_flag = other_gameobj.is_doomed_flag;
    other_gameobj.is_doomed_flag = temp_flag;

    Handle<GameObject> temp_gameobj_handle = gameobject_handle;
    gameobject_handle = other_gameobj.gameobject_handle;
    other_gameobj.gameobject_handle = temp_gameobj_handle;

    Handle<Transform> temp_transform_handle = transform_handle;
    transform_handle = other_gameobj.transform_handle;
    other_gameobj.transform_handle = temp_transform_handle;

    Handle<LogicHub> temp_logichub_handle = logichub_handle;
    logichub_handle = other_gameobj.logichub_handle;
    other_gameobj.logichub_handle = temp_logichub_handle;

    std::string temp_string = get_log_id();
    set_log_id(other_gameobj.get_log_id());
    other_gameobj.set_log_id(temp_string);

}

Scene *GameObject::get_scene() {
    return m_scene;
}

bool GameObject::has_component(const std::string &id) {
    return (m_components_mapped_array[ComponentFactory::id_to_index(id)] != -1);
}

void GameObject::doom_component(const std::string &id) {
    if (id == "Transform" || id == "LogicHub") {
        LOG_ERROR << "It's not possible to remove Transform or LogicHub components";
        exit(1);
    }

    unsigned int type_index = ComponentFactory::id_to_index(id);
    int comp_index = m_components_mapped_array[type_index];

    if (comp_index >= 0) {
        m_scene->get_component_memorylayer_array()[type_index]->remove_unspecified_component(comp_index);
        m_components_mapped_array[type_index] = -1;

    } else {
        LOG_ERROR << "Error: Tried to remove an inexistent component with id [" << id << "]";
        exit(1);
    }
}

unsigned int GameObject::add_unspecified_component(const std::string &id) {
    LOG_DEBUG(19) << "Adding a new component of id [" + id + "]";
    unsigned int type_index = ComponentFactory::id_to_index(id);
    auto yo = m_scene->get_component_memorylayer_array();
    m_components_mapped_array[type_index] = yo[type_index]->create_unspecified_component(this->get_handle());
    return m_components_mapped_array[type_index];
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










