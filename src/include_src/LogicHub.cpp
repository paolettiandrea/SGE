
#include <SGE/components/LogicHub.hpp>

#include "LogicHub.hpp"
#include "Logic.hpp"


LogicHub::LogicHub(const Handle<GameObject> &gameobject) : Component(gameobject, "LogicHub") {}

void LogicHub::attach_logic(Logic *new_logic) {
    LOG_DEBUG(18) << "Attaching new logic with logic id (" << new_logic->get_logic_id() << ")";

    attached_logic_list.push_back(new_logic);
    new_logic->update_references(this->gameobject());
    new_logic->on_start();
}

bool LogicHub::has_logic(const std::string &logic_id) {
    for (auto attached_logic : attached_logic_list) {
        if (attached_logic->get_logic_id() == logic_id) return true;
    }
    return false;
}

bool LogicHub::has_logic(Logic *target_logic) {
    for (auto attached_logic : attached_logic_list) {
        if (attached_logic == target_logic) return true;
    }
    return false;
}

void LogicHub::remove_logic(Logic *target_logic) {
    attached_logic_list.remove(target_logic);
    target_logic->on_destruction();
    delete(target_logic);
}

LogicHub::~LogicHub() {

}

Logic *LogicHub::get_unspecificed_logic(const std::string &logic_id) {
    for (auto attached_logic : attached_logic_list) {
        if (attached_logic->get_logic_id() == logic_id) return attached_logic;
    }
    return nullptr;
}

//region Callback propagation methods

void LogicHub::on_start() {
    for (auto logic : attached_logic_list) {
        logic->on_start();
    }
}

void LogicHub::on_destruction() {
    for (auto logic : attached_logic_list) {
        logic->on_destruction();
    }
}

void LogicHub::on_update() {
    for (auto logic : attached_logic_list) {
        logic->on_update();
    }
}

void LogicHub::on_fixed_update() {
    for (auto logic : attached_logic_list) {
        logic->on_fixed_update();
    }
}

void LogicHub::destruction_callback() {
    LOG_DEBUG(20) << "Destroying attached logic";
    for (auto logic : attached_logic_list) {
        delete(logic);
    }
}
//endregion






