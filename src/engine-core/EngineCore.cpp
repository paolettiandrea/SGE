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
    // Calculate the elapsed time since the last start of the game loop and add it to the accumulator
    time_point<steady_clock> temp_now = steady_clock::now();
    duration<double, std::ratio<1>> duration_since_last_loop_start = steady_clock::now() - last_loop_start_time;
    last_loop_start_time = temp_now;
    m_delta_time = duration_since_last_loop_start.count();
    m_physics_time_accumulator += duration_since_last_loop_start.count();

    LOG_DEBUG(20) << "Game_loop is starting |" << object_manager.get_top_scene()->get_log_id()
                  << " | stack_size:" << object_manager.get_scene_stack_size() << " | delta_time:"<< m_delta_time;

    // Ensure plenty of space in the component vectors in order to avoid reallocation in awkward moments
    // and to ensure pointer validity during a given frame
    memory_buffer_pass();
    
    // EVENTS
    input_manager.reset_volatile();
    handle_events();

    // PHYSICS: consume the accumulated time executing phisics steps
    double fixed_delta = physics_manager.fixed_delta_time();
    while (m_physics_time_accumulator > fixed_delta) {
        LOG_DEBUG(30) << "Fixed Update";
        logic_manager.on_fixed_update();
        physics_manager.collider_clean_pass();
        physics_manager.kinematic_transform_to_body();
        physics_manager.step(*object_manager.get_top_scene()->get_b2World());
        physics_manager.dynamic_body_to_transform_update();                 // Updates the GameObjects with Rigidbodies' position and rotation according to their simulated body
        m_physics_time_accumulator -= fixed_delta;
    }



    logic_manager.on_update();

    // Destroys the GameObjects and Components
    object_manager.doom_pass();

    visual_debug_pass();

    // RENDER
    window_manager.prepare_render();
    window_manager.clear_window();
    window_manager.draw();
    window_manager.display();

    // Modify the Scene stack if requested during this loop
    bool scene_stack_modified = object_manager.scene_pass();
    if (scene_stack_modified) {
        if (object_manager.get_scene_stack_size()==0) return false;
        // Since the scene stack was modified update the pointer to the active camera for the window manager
        window_manager.update_active_camera(object_manager.get_top_scene()->get_camera());

    }

    m_frame_counter++;

    LOG_DEBUG(20) << "Game_loop ended";

    return true;
}


void EngineCore::initialize(cd::SceneConstructionData& initial_scene_cd) {
    LOG_INFO << "Initialization started";
    Scene* initial_scene = object_manager.push_new_scene(&initial_scene_cd);
    last_loop_start_time = std::chrono::steady_clock::now();
    window_manager.update_active_camera(initial_scene->get_camera());
    physics_manager.update_active_world(object_manager.get_top_scene()->get_b2World());
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

bool sge::core::EngineCore::is_mouse_down(sf::Mouse::Button button) {
    return input_manager.is_mouse_down(button);
}

bool sge::core::EngineCore::is_mouse_released(sf::Mouse::Button button) {
    return input_manager.is_mouse_released(button);
}

bool sge::core::EngineCore::is_mouse_pressed(sf::Mouse::Button button) {
    return input_manager.is_mouse_pressed(button);
}

bool sge::core::EngineCore::is_key_down(sf::Keyboard::Key key) {
    return input_manager.is_key_down(key);
}

bool sge::core::EngineCore::is_key_pressed(sf::Keyboard::Key key) {
    return input_manager.is_key_pressed(key);
}

bool sge::core::EngineCore::is_key_released(sf::Keyboard::Key key) {
    return input_manager.is_key_released(key);
}

void sge::core::EngineCore::handle_events() {
    sf::Event event;
    while (window_manager.m_window.pollEvent(event))
    {

        switch (event.type){
            case sf::Event::Closed:
                window_manager.m_window.close();
                break;
            case sf::Event::Resized:
                window_manager.update_camera_ratio();
                break;

            // Input events (mouse and keyboard presses and releases)
            case sf::Event::MouseButtonPressed:
                input_manager.pressed_mouse_callback(event.mouseButton.button);
                break;
            case sf::Event::MouseButtonReleased:
                input_manager.released_mouse_callback(event.mouseButton.button);
                break;
            case sf::Event::KeyPressed:
                input_manager.pressed_key_callback(event.key.code);
                break;
            case sf::Event::KeyReleased:
                input_manager.released_key_callback(event.key.code);
        }
    }


    // VISUAL DEBUG toggles
#if DEBUG
    if (input_manager.is_key_down(sf::Keyboard::LShift) || input_manager.is_key_down(sf::Keyboard::RShift)){
        if (input_manager.is_key_pressed(sf::Keyboard::T)) object_manager.toggle_visual_debug_transform();
        if (input_manager.is_key_pressed(sf::Keyboard::N)) object_manager.toggle_visual_debug_names();

        if (input_manager.is_key_pressed(sf::Keyboard::P)) window_manager.toggle_visual_debug_path();
        if (input_manager.is_key_pressed(sf::Keyboard::S)) window_manager.toggle_visual_debug_triangle_strip();

        if (input_manager.is_key_pressed(sf::Keyboard::C)) physics_manager.toggle_visual_debug_collider();
    }
#endif

}

void sge::core::EngineCore::memory_buffer_pass() {
    input_manager.memory_buffer_pass();
    logic_manager.memory_buffer_pass();
    object_manager.memory_buffer_pass();
    window_manager.memory_buffer_pass();
    physics_manager.memory_buffer_pass();

}
//endregion


