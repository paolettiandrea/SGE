#include "EngineCore.hpp"
#include "SGE/debug/PointDebugShape.hpp"
#include "SGE/debug/LineDebugShape.hpp"
#include "SGE/debug/PathDebugShape.hpp"
#include "SGE/debug/CircleDebugShape.hpp"
#include "SGE/debug/DirectionDebugShape.hpp"

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
    m_physics_time_accumulator += duration_since_last_loop_start.count();

    LOG_DEBUG(20) << "Game_loop is starting |" << object_manager.get_top_scene()->get_log_id()
                  << " | stack_size:" << object_manager.get_scene_stack_size() << " | delta_time:"<< m_delta_time;

    // PHYSICS: consume the accumulated time executing phisics steps
    double fixed_delta = physics_manager.fixed_delta_time();
    while (m_physics_time_accumulator > fixed_delta) {
        LOG_DEBUG(30) << "Fixed Update";
        logic_manager.on_fixed_update();
        physics_manager.clean_pass();
        physics_manager.step(*object_manager.get_top_scene()->get_b2World());
        m_physics_time_accumulator -= fixed_delta;
    }
    // Updates the GameObjects with Rigidbodies' position and rotation according to their simulated body
    physics_manager.update_transform();


    logic_manager.on_update();

    // Destroys the GameObjects and Components
    object_manager.doom_pass();

    visual_debug_pass();

    // RENDER
    window_manager.handle_window_events();
    window_manager.clear_window();
    window_manager.draw();
    window_manager.display();

    // Modify the Scene stack if requested during this loop
    object_manager.scene_pass();

    m_frame_counter++;

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
    return  m_frame_counter;
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


sge::Camera* sge::core::EngineCore::get_camera() {
    return &window_manager.m_camera;
}

bool sge::core::EngineCore::is_shutting_down() {
    return m_shutting_down_flag;
}

double sge::core::EngineCore::fixed_delta_time() {
    return physics_manager.fixed_delta_time();
}

void sge::core::EngineCore::debug_draw_point(const sge::Vec2<float>& point, float duration, const std::string& label, unsigned int digits, sf::Color color) {
    window_manager.debug_shapes_manager.add_debug_shape(new sge::debug::PointDebugShape(point.x,point.y,duration,label,digits,color));
}

void sge::core::EngineCore::debug_draw_line(const sge::Vec2<float>& point1, const sge::Vec2<float>& point2, float duration, const std::string& label, unsigned int digits, sf::Color color) {
    window_manager.debug_shapes_manager.add_debug_shape(new debug::LineDebugShape(point1.x,point1.y,point2.x,point2.y,duration,digits,label,color));
}

void sge::core::EngineCore::debug_draw_path(sge::Path path, float duration, const std::string& label, unsigned int decimals, sf::Color color) {
    window_manager.debug_shapes_manager.add_debug_shape(new debug::PathDebugShape(path,duration,label,decimals,color));
}

void sge::core::EngineCore::debug_draw_circle(sge::Vec2<float> center_pos, float radius, float duration, const std::string& label, unsigned int decimals, sf::Color color) {
    window_manager.debug_shapes_manager.add_debug_shape(new debug::CircleDebugShape(center_pos,radius,duration,label,decimals,color));
}

void sge::core::EngineCore::debug_draw_direction(sge::Vec2<float> from, sge::Vec2<float> to, float duration, sf::Color color) {
    window_manager.debug_shapes_manager.add_debug_shape(new debug::DirectionDebugShape(from,to,duration,color));

}

void sge::core::EngineCore::visual_debug_pass() {
    object_manager.visual_debug_pass();
    logic_manager.visual_debug_pass();
    window_manager.visual_debug_pass();
    physics_manager.visual_debug_pass();
}
//endregion


