#include "LogicManager.hpp"

using sge::core::LogicManager;

sge::core::LogicManager::~LogicManager() {

}

LogicManager::LogicManager()
    : Subsystem("LOGIC SUBSYSTEM")
    , logichub_creator("LogicHub"){
}

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

void sge::core::LogicManager::ensure_logichub_free_space() {
    logichub_creator.ensure_space_comp_vector(SGE_LOGICHUB_BUFFER_SIZE);

}
