#include <SGE/logic/Logic.hpp>

using namespace sge;
using utils::Handle;

Logic::~Logic() {
    LOG_DEBUG(25) << "Destructor";
}

void Logic::update_references(Handle<GameObject> gameobj) {
    this->set_log_id("(" + this->get_logic_id() + ") of " + gameobj->get_log_id());

    m_gameobject_handle = gameobj;
    m_scene = m_gameobject_handle->get_scene();
    m_env = m_scene->env();
}

Handle<GameObject> Logic::gameobject() {
    return m_gameobject_handle;
}

Scene *Logic::scene() {
    return gameobject()->get_scene();
}

IEnvironment *Logic::env() {
    return m_env;
}

void Logic::doom() {
    is_doomed_flag = true;
}

bool Logic::is_doomed() {
    return is_doomed_flag;
}








