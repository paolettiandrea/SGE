#include "Component.hpp"
#include "GameObject.hpp"


Component::Component(Handle<GameObject> gameobject, const std::string &id)
    : Loggable( "[" + id + "] of " + gameobject->get_log_id())
    , gameobject_handle(gameobject) {

}

Handle<GameObject> &Component::gameobject() {
    return gameobject_handle;
}

void Component::destroy() { is_doomed_flag = true; }
