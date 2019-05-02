
#include <SGE/engine/Engine.hpp>

#include "SGE/engine/Engine.hpp"
#include "EngineCore.hpp"

Engine::Engine()
    : Loggable("ENGINE") {
    LOG_DEBUG(10) << "Initiating construction";
    core = new EngineCore();
}

Engine::~Engine() {
    delete core;
}

bool Engine::game_loop() {
    return core->game_loop();
}

void Engine::initialize(Logic *initial_logic) {
    core->initialize(initial_logic);
}


