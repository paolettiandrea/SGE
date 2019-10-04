#include "LogicManager.hpp"

using sge::core::LogicManager;

sge::core::LogicManager::~LogicManager() {

}

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

    for (int i = 0; i < vector.size(); ++i) {
        auto handle = vector[i];
        auto pointer = handle.get_yo();
        handle->on_update();
    }
    LOG_DEBUG(15) << "Terminating on_update";
}
