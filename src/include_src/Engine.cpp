
#include <SGE/engine/Engine.hpp>

#include "SGE/engine/Engine.hpp"
#include "EngineCore.hpp"

using namespace sge;
using namespace sge::core;

Engine::Engine(cd::EngineCore_ConstructionData& data)
    : Loggable("ENGINE") {
    LOG_DEBUG(10) << "Initiating construction";
    core = new EngineCore(data);
}

Engine::~Engine() {
    LOG_INFO << "Starting engine deletion";
    delete core;
}

bool Engine::game_loop() {
    return core->game_loop();
}

void Engine::initialize(cd::SceneConstructionData& initial_scene_cd) {
    core->initialize(initial_scene_cd);
}

IEnvironment *Engine::env() {
    return (IEnvironment*)core;
}


