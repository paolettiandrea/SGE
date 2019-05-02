//
// Created by andrea on 4/30/19.
//

#include "LogicManager.hpp"

LogicManager::LogicManager()
    : Subsystem("LOGIC SUBSYSTEM")
    , logichub_creator("LogicHub"){}

void LogicManager::on_fixed_update() {
    auto vector = logichub_creator.get_top_layer()->get_component_vector();
    for (auto logichub : vector) {
        logichub->on_fixed_update();
    }
}

void LogicManager::on_update() {
    LOG_DEBUG(15) << "Starting on_update";
    auto vector = logichub_creator.get_top_layer()->get_component_vector();
    for (auto logichub : vector) {
        logichub->on_update();
    }
    LOG_DEBUG(15) << "Terminating on_update";
}
