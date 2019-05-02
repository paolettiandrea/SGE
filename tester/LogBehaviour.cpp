//
// Created by andrea on 4/30/19.
//

#include "LogBehaviour.hpp"

std::string LogBehaviour::get_logic_type_id() {
    return "LogBehaviour";
}

void LogBehaviour::on_start() {
    LOG(10) << "on_start";
    env()->doom_top_scene();
}

void LogBehaviour::on_destruction() {
    LOG(10) << "on_destruction";
}

void LogBehaviour::on_update() {
    LOG_DEBUG(10) << "on_update";
}

void LogBehaviour::on_fixed_update() {
    LOG_DEBUG(10) << "on_fixed_update";
}
