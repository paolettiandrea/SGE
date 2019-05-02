#include "EngineCore.hpp"


EngineCore::EngineCore()
    : Loggable("ENGINE CORE")
    , object_manager((IEnvironment*)this) {

}

bool EngineCore::game_loop() {
    if (object_manager.get_scene_stack_size()==0) return false;

    LOG_DEBUG(21) << "Starting on_update";
    logic_manager.on_update();

    LOG_DEBUG(21) << "Starting doom_pass";
    object_manager.doom_pass();
    return true;
}

void EngineCore::initialize(Logic *initial_logic) {
    Scene* scene = object_manager.push_new_scene(initial_logic);

}



//region IEnvironment definitions

double EngineCore::delta_time() {
    return 0;
}

double EngineCore::fixed_delta_time() {
    return 0;
}
//endregion
