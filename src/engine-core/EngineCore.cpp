#include "EngineCore.hpp"

using sge::core::EngineCore;
using sge::cd::SceneConstructionData;


bool EngineCore::game_loop() {
    if (object_manager.get_scene_stack_size()==0 || !window_manager.window_is_open()) return false;

    using namespace std::chrono;
    // Calculate the elapsed time since the last transfer to the accumulator and add it to the accumulator
    time_point<steady_clock> temp_now = steady_clock::now();
    duration<double, std::ratio<1>> duration_since_last_loop_start = steady_clock::now() - last_toop_start_time;
    last_toop_start_time = temp_now;
    m_delta_time = duration_since_last_loop_start.count();

    LOG_DEBUG(20) << "Game_loop is starting |" << object_manager.get_top_scene()->get_log_id()
                  << " | stack_size:" << object_manager.get_scene_stack_size() << " | delta_time:"<< m_delta_time;


    logic_manager.on_update();

    object_manager.doom_pass();

    window_manager.handle_window_events();
    window_manager.clear_window();
    window_manager.draw();
    window_manager.display();

    object_manager.scene_pass();        // Where the scene is changed if requested during this loop

    frame_counter++;
    LOG_DEBUG(20) << "Game_loop ended";
    return true;
}

void EngineCore::initialize(cd::SceneConstructionData& initial_scene_cd) {
    LOG_INFO << "Initialization started";
    Scene* scene = object_manager.push_new_scene(&initial_scene_cd);
    last_toop_start_time = std::chrono::steady_clock::now();
    LOG_INFO << "Initialization completed";
}



//region IEnvironment definitions

double EngineCore::delta_time() {
    return m_delta_time;
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
    m_shutting_down_flag = true;
    LOG_DEBUG(20) << "Destructor";
    while (object_manager.get_scene_stack_size() > 0){
        LOG_DEBUG(20) << "Still " << object_manager.get_scene_stack_size()
                      << " scenes remaining in the stack, popping top " << object_manager.get_top_scene()->get_log_id();
        object_manager.pop_top_scene();
    }
}

void sge::core::EngineCore::debug_draw(sge::debug::DebugShape *new_debug_shape) {
    window_manager.debug_shapes_manager.add_debug_shape(new_debug_shape);
}



/*double EngineCore::fixed_delta_time() {
    return 0;
}*/
//endregion


sge::Camera* sge::core::EngineCore::get_camera() {
    return &window_manager.m_camera;
}

bool sge::core::EngineCore::is_shutting_down() {
    return m_shutting_down_flag;
}
