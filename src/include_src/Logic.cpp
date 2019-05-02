#include <SGE/logic/Logic.hpp>

void Logic::on_start() { }

void Logic::on_destruction() { }

void Logic::on_update() { }

void Logic::on_fixed_update() { }

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

