#include "Component.hpp"
#include "GameObject.hpp"

using sge::cmp::Component;
using sge::GameObject;
using utils::Handle;

Component::Component(Handle<GameObject> gameobject, const std::string &id)
    : Loggable( "[" + id + "] of " + gameobject->get_log_id())
    , gameobject_handle(gameobject) {

}


Handle<GameObject> &Component::gameobject() {
    return gameobject_handle;
}

void Component::doom() {
    LOG_DEBUG(35) << "Doomed";
    is_doomed_flag = true;
}


