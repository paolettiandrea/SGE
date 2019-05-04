#include "EngineCore.hpp"

using sge::core::EngineCore;
using sge::cd::SceneConstructionData;


bool EngineCore::game_loop() {
    if (object_manager.get_scene_stack_size()==0 || !window_manager.window_is_open()) return false;
    LOG_DEBUG(20) << "The game_loop is starting with " << object_manager.get_top_scene()->get_log_id()
                  << " on top of a scene stack of size " << object_manager.get_scene_stack_size();

    logic_manager.on_update();

    // End-loop passes
    object_manager.doom_pass();

    window_manager.handle_window_events();
    window_manager.clear_window();

    window_manager.display();

    object_manager.scene_pass();        // Where the scene is changed if requested during this loop

    frame_counter++;
    LOG_DEBUG(20) << "Game_loop ended";
    return true;
}

void EngineCore::initialize(cd::SceneConstructionData& initial_scene_cd) {
    LOG_INFO << "Initialization started";
    Scene* scene = object_manager.push_new_scene(&initial_scene_cd);
    LOG_INFO << "Initialization completed";
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

unsigned int EngineCore::frame_count() {
    return  frame_counter;
}

EngineCore::~EngineCore() {
    LOG_DEBUG(20) << "Destructor";
    while (object_manager.get_scene_stack_size() > 0){
        LOG_DEBUG(20) << "Still " << object_manager.get_scene_stack_size()
                      << " scenes remaining in the stack, popping top " << object_manager.get_top_scene()->get_log_id();
        object_manager.pop_top_scene();
    }
}

/*double EngineCore::fixed_delta_time() {
    return 0;
}*/
//endregion
