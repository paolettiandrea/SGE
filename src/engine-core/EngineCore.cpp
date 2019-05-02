#include "EngineCore.hpp"


EngineCore::EngineCore()
    : Loggable("ENGINE CORE")
    , object_manager((IEnvironment*)this) {

}

bool EngineCore::game_loop() {
    if (object_manager.get_scene_stack_size()==0) return false;
    LOG_DEBUG(20) << "The game_loop is starting again with " << object_manager.get_top_scene()->get_log_id()
                  << " on top of a scene stack of size " << object_manager.get_scene_stack_size();

    LOG_DEBUG(21) << "Starting on_update";
    logic_manager.on_update();

    LOG_DEBUG(21) << "Starting doom_pass";
    object_manager.doom_pass();
    LOG_DEBUG(21) << "Starting scene_pass";
    object_manager.scene_pass();
    return true;
}

void EngineCore::initialize(Logic *initial_logic) {
    SceneConstructionData* data = new SceneConstructionData("Initial Scene");
    data->initial_logic = initial_logic;
    Scene* scene = object_manager.push_new_scene(data);
    delete(data);

}



//region IEnvironment definitions

double EngineCore::delta_time() {
    return 0;
}

bool EngineCore::book_new_scene_push(const std::string &name, Logic *initial_logic) {
    return object_manager.book_scene_push(name, initial_logic);
}

void EngineCore::doom_top_scene() {
    object_manager.doom_top_scene();
}

/*double EngineCore::fixed_delta_time() {
    return 0;
}*/
//endregion
