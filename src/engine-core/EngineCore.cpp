#include "EngineCore.hpp"


bool EngineCore::game_loop() {
    if (object_manager.get_scene_stack_size()==0) return false;

    logic_manager.on_update();

    object_manager.doom_pass();
    return true;
}

void EngineCore::initialize(Logic *initial_logic) {
    Scene* scene = object_manager.push_new_scene(initial_logic);

}

EngineCore::EngineCore() : Loggable("ENGINE CORE") {

}
