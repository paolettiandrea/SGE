#include "SGE/GameObject.hpp"

#include <iostream>
#include "ComponentFactory.hpp"
#include "IComponentMemoryLayer.hpp"
#include "Scene.hpp"
#include "Logic.hpp"

using namespace sge;
using namespace sge::core;
using namespace sge::cmp;
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
    auto transform = add_component<Transform>("Transform");
    transform_handle = transform;
    logichub_handle = add_component<LogicHub>("LogicHub");
}

GameObject::~GameObject() {
    LOG_DEBUG(19) << "Destruction";

}

void GameObject::doom() {
    LOG_DEBUG(32) << "Doomed";
    recursive_doom(get_handle());
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

    auto temp_id = get_log_id();


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

    //update handles
    gameobject_handle.update_origin_pointer(&other_gameobj);
    other_gameobj.gameobject_handle.update_origin_pointer(this);

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

Handle<Transform> &GameObject::transform() {
    return transform_handle;
}

 Handle<LogicHub> &GameObject::logichub() {
    return logichub_handle;
}

std::string GameObject::get_string_attached_components() {
    std::string out_str;
    for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
        if (m_components_mapped_array[i]!=-1) {
            out_str += ComponentFactory::index_to_id(i);
            if (i!=TOTAL_POSSIBLE_COMPONENTS-1) {
                out_str += "]-[";
            }
        }
    }
    return out_str;
}


std::string sge::GameObject::get_string_local_hierarchy(bool print_components) {
    std::string out_str;
    recursive_get_string_local_hierarchy(out_str, 0, print_components);
    return out_str;
}

std::string sge::GameObject::recursive_get_string_local_hierarchy(std::string &out_str, unsigned int indentation, bool print_components) {
    for (int i = 0; i < indentation; ++i)
        out_str += "\t";

    out_str += get_log_id();

    if (print_components) {
        out_str += "   [" + get_string_attached_components() + "]";
    }

    out_str+= "\n";

    for (auto child : transform()->get_children_list()) {
        child->gameobject()->recursive_get_string_local_hierarchy(out_str, indentation+1, print_components);
    }
    return out_str;
}

void GameObject::recursive_doom(utils::Handle<GameObject> pointed) {
    for (auto child: pointed->transform()->get_children()) {
        recursive_doom(child->gameobject());
    }
    pointed->is_doomed_flag = true;
}










