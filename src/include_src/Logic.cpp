#include <SGE/logic/Logic.hpp>

void Logic::on_start() { }

void Logic::on_destruction() { }

void Logic::on_update() { }

void Logic::on_fixed_update() { }

Logic::~Logic() { }

void Logic::update_references(Handle<GameObject> gameobj) {
    this->set_log_id("(" + this->get_logic_id() + ") of " + gameobj->get_log_id());

    gameobject_handle = gameobj;
}

Handle<GameObject> Logic::gameobject() {
    return gameobject_handle;
}

