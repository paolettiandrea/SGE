//
// Created by andrea on 4/30/19.
//

#include "InitialDummyLogic.hpp"

std::string InitialDummyLogic::get_logic_id() {
    return "InitialDummyLogic";
}

void InitialDummyLogic::on_start() {
    LOG(10) << "on_start";
    gameobject()->add_unspecified_component("Path");
    gameobject()->remove_component("Path");


}

void InitialDummyLogic::on_destruction() {
    LOG(10) << "on_destruction";
}

void InitialDummyLogic::on_update() {
    LOG_DEBUG(10) << "on_update";
}

void InitialDummyLogic::on_fixed_update() {
    LOG_DEBUG(10) << "on_fixed_update";
}
