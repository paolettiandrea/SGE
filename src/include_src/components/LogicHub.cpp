
#include <SGE/components/LogicHub.hpp>

#include "LogicHub.hpp"
#include "Logic.hpp"

using sge::cmp::LogicHub;
using sge::Logic;
using utils::Handle;

LogicHub::LogicHub(const Handle<GameObject> &gameobject)
    : Component(gameobject, "LogicHub") {
}


void LogicHub::attach_logic(Logic *new_logic) {
    LOG_DEBUG(18) << "Attaching new logic with logic id (" << new_logic->get_logic_id() << ")";

    attached_logic_list.push_back(new_logic);
    new_logic->update_references(this->gameobject());
    LOG_DEBUG(18) << "Calling on_start on the newly attached logic";
    new_logic->on_start();
}

bool LogicHub::has_logic(const std::string &logic_type_id) {
    for (auto attached_logic : attached_logic_list) {
        if (attached_logic->get_logic_id() == logic_type_id) return true;
    }
    return false;
}


void LogicHub::remove_logic(Logic *target_logic) {
    for (int i = 0; i < attached_logic_list.size(); ++i) {
        if (attached_logic_list[i] == target_logic) {
            if (i!=attached_logic_list.size()-1 && attached_logic_list.size()>1) {
                attached_logic_list[i] = attached_logic_list[attached_logic_list.size() - 1];
            }
            break;
        }
    }
    attached_logic_list.pop_back();
    delete(target_logic);
    // TODO some sort of removal callback here, probably also an Event for other object to subscribe
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
    IComponent::destruction_callback();
    LOG_DEBUG(20) << "Destroying attached logic";
    for (auto logic : attached_logic_list) {
        delete(logic);
    }
}

void sge::cmp::LogicHub::on_collision_end(CollisionInfo &collision_info) {
    for (auto logic : attached_logic_list) {
        logic->on_collision_end(collision_info);
    }
}

void sge::cmp::LogicHub::on_collision_begin(CollisionInfo &collision_info) {
    for (auto logic : attached_logic_list) {
        logic->on_collision_begin(collision_info);
    }
}

void sge::cmp::LogicHub::pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const CollisionInfo &info) {
    for (auto logic : attached_logic_list) {
        logic->pre_solve(contact, oldManifold, info);
    }
}

void sge::cmp::LogicHub::post_solve(b2Contact *contact, const b2ContactImpulse *impulse, const CollisionInfo &info) {
    for (auto logic : attached_logic_list) {
        logic->post_solve(contact, impulse, info);
    }
}
//endregion

std::string sge::cmp::LogicHub::get_debug_string() {
    std::string s;

    s += "Attached Logics: " + std::to_string(attached_logic_list.size()) + "";

    return s;
}

const std::vector<Logic *> &sge::cmp::LogicHub::get_attached_logic_list() const {
    return attached_logic_list;
}

void sge::cmp::LogicHub::on_scene_destruction() {
    for (auto logic : attached_logic_list) {
        logic->on_scene_destruction();
    }
}

void sge::cmp::LogicHub::on_scene_pause() {
    for (auto logic : attached_logic_list) {
        logic->on_scene_pause();
    }
}

void sge::cmp::LogicHub::on_scene_resume() {
    for (auto logic : attached_logic_list) {
        logic->on_scene_resume();
    }
}

void sge::cmp::LogicHub::doom_pass() {
    std::vector<Logic*> new_vec;
    for (auto logic : attached_logic_list) {
        if (logic->is_doomed()) {
            delete (logic);
        } else {
            new_vec.push_back(logic);
        }
    }

    attached_logic_list = new_vec;
}






