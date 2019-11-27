#include "IComponent.hpp"
#include "GameObject.hpp"

using sge::cmp::IComponent;
using sge::GameObject;
using utils::Handle;

IComponent::IComponent(Handle<GameObject> gameobject, const std::string &id)
        : Loggable( "[" + id + "] of " + gameobject->get_log_id())
        , gameobject_handle(gameobject) {

}


Handle<GameObject> IComponent::gameobject() {
    return gameobject_handle;
}

void IComponent::doom() {
    LOG_DEBUG(35) << "Doomed";
    is_doomed_flag = true;
}

utils::Handle<sge::GameObject> sge::cmp::IComponent::gameobject() const {
    return gameobject_handle;
}

std::string sge::cmp::IComponent::get_debug_string() {
    return std::string();
}

