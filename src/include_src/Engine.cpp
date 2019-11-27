
#include <SGE/engine/Engine.hpp>

#if DEBUG
    #include "debug/EngineCoreDebug.hpp"
#else
    #include "EngineCore.hpp"
#endif


using namespace sge;
using namespace sge::core;

Engine::Engine(cd::Engine_ConstructionData& data)
    : Loggable("ENGINE") {
    LOG_DEBUG(10) << "Initiating construction";

#if DEBUG
    core = new EngineCoreDebug(data);
#else
    core = new EngineCore(data);
#endif
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


