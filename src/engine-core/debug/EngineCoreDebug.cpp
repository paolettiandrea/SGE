#include "EngineCoreDebug.hpp"

sge::core::EngineCoreDebug::EngineCoreDebug(sge::cd::Engine_ConstructionData &data) : EngineCore(data) {
    hierarchy_panel.initialize(window_manager.font_manager);
}

void sge::core::EngineCoreDebug::physics_routine() {
    double fixed_delta = physics_manager.fixed_delta_time();
    while (m_physics_time_accumulator > fixed_delta) {
        LOG_DEBUG(30) << "Fixed Update";
        profiler.start("Fixed Update");
        logic_manager.on_fixed_update();
        profiler.stop("Fixed Update");
        profiler.start("Physics");
        physics_manager.collider_clean_pass();
        physics_manager.kinematic_transform_to_body();
        physics_manager.step(*object_manager.get_top_scene()->get_b2World());
        physics_manager.dynamic_body_to_transform_update();                 // Updates the GameObjects with Rigidbodies' position and rotation according to their simulated body
        physics_manager.trigger_collision_callbacks();
        m_physics_time_accumulator -= fixed_delta;
        profiler.stop("Physics");
    }
}

void sge::core::EngineCoreDebug::render_routine() {
    window_manager.prepare_render();
    profiler.start("Draw");
    window_manager.draw();
    profiler.stop("Draw");

    handle_debug_input();

    sf::RenderTexture render_texture;
    auto port =window_manager. m_window.getViewport(window_manager.active_camera->get_view());
    sf::IntRect rect(port);
    render_texture.create(rect.width, rect.height);
    render_texture.clear(sf::Color::Transparent);

    if (hierarchy_active) {
        hierarchy_panel.update_state(object_manager.transform_creator.get_top_layer()->get_component_vector(), object_manager.scene_cd_vec);
        render_texture.draw(hierarchy_panel);
    }

    if (profiler_active) {
        profiler.draw(render_texture, sf::RenderStates(), rect.width, rect.height);
    }

    render_texture.display();


    sf::Sprite sprite(render_texture.getTexture(), rect);
    auto temp = sf::Vector2<float>(window_manager.active_camera->get_view().getSize().x/rect.width, window_manager.active_camera->get_view().getSize().y/rect.height);
    sprite.setScale(temp);

    auto camera_pos = window_manager.active_camera->get_view().getCenter();
    sprite.setPosition(camera_pos.x - window_manager.active_camera->get_view().getSize().x/2, camera_pos.y - window_manager.active_camera->get_view().getSize().y/2);
    window_manager.m_window.draw(sprite);

    profiler.start("Display");
    window_manager.display();
    profiler.stop("Display");
}

void sge::core::EngineCoreDebug::handle_debug_input() {
    if (input_manager.is_key_down(SGE_DEBUG_MAIN_KEY1) || input_manager.is_key_down(SGE_DEBUG_MAIN_KEY2)) {

        // Hierarchy
        if (input_manager.is_key_pressed(sf::Keyboard::V)) {
            hierarchy_active = !hierarchy_active;
        }
        if (hierarchy_active) {
            if (input_manager.is_key_pressed(sf::Keyboard::Down)) {
                hierarchy_panel.focus_next();
            }
            if (input_manager.is_key_pressed(sf::Keyboard::Up)) {
                hierarchy_panel.focus_previous();
            }
            if (input_manager.is_key_pressed(sf::Keyboard::Left)) {
                hierarchy_panel.prev_mode();
            }
            if (input_manager.is_key_pressed(sf::Keyboard::Right)) {
                hierarchy_panel.next_mode();
            }

            if (input_manager.is_key_pressed(sf::Keyboard::Return)) {
                hierarchy_panel.enter_focused();
            }
            if (input_manager.is_key_pressed(sf::Keyboard::BackSpace)) {
                hierarchy_panel.return_focused();
            }
        }

        // Profiler
        if (input_manager.is_key_pressed(sf::Keyboard::P)) {
            profiler_active = !profiler_active;
        }
    }
}

bool sge::core::EngineCoreDebug::game_loop() {
    if (object_manager.get_scene_stack_size()==0 || !window_manager.window_is_open()) return false;
    // Calculate the elapsed time since the last start of the game loop and add it to the accumulator
    update_accumulator();

    LOG_DEBUG(20) << "Game_loop is starting |" << object_manager.get_top_scene()->get_log_id()
                  << " | stack_size:" << object_manager.get_scene_stack_size() << " | delta_time:"<< m_delta_time;

    // Ensure plenty of space in the component vectors in order to avoid reallocation in awkward moments
    // and to ensure pointer validity during a given frame
    memory_buffer_pass();

    // EVENTS
    input_manager.reset_volatile();
    handle_events();

    // PHYSICS: consume the accumulated time executing phisics steps
    physics_routine();
    profiler.start("Update");
    logic_manager.on_update();
    profiler.stop("Update");


    profiler.start("Debug");
    visual_debug_pass();
    profiler.stop("Debug");

    // Destroys the GameObjects and Components
    object_manager.doom_pass();


    // RENDER
    render_routine();

    // Modify the Scene stack if requested during this loop
    bool scene_stack_modified = object_manager.scene_pass();
    if (scene_stack_modified) {
        if (object_manager.get_scene_stack_size()==0) return false;
        // Since the scene stack was modified update the pointer to the active camera for the window manager
        window_manager.update_active_camera(object_manager.get_top_scene()->get_camera());

    }

    m_frame_counter++;

    LOG_DEBUG(20) << "Game_loop ended\n\n";

    profiler.increase_dump_counter();

    return true;
}









