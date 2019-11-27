#include "EngineCoreDebug.hpp"

sge::core::EngineCoreDebug::EngineCoreDebug(sge::cd::Engine_ConstructionData &data) : EngineCore(data) {
    hierarchy_panel.initialize(window_manager.font_manager);
}



void sge::core::EngineCoreDebug::render_routine() {
    window_manager.prepare_render();
    //profiler.start("Draw");
    window_manager.draw();
    //profiler.stop("Draw");

    handle_debug_input();

    sf::RenderTexture render_texture;
    auto port =window_manager. m_window.getViewport(window_manager.active_camera->get_view());
    sf::IntRect rect(port);
    render_texture.create(rect.width, rect.height);
    render_texture.clear(sf::Color::Transparent);

    hierarchy_panel.update_state(object_manager.transform_creator.get_top_layer()->get_component_vector(), object_manager.scene_cd_vec);

    render_texture.draw(hierarchy_panel);

    render_texture.display();


    sf::Sprite sprite(render_texture.getTexture(), rect);
    auto temp = sf::Vector2<float>(window_manager.active_camera->get_view().getSize().x/rect.width, window_manager.active_camera->get_view().getSize().y/rect.height);
    sprite.setScale(temp);

    auto camera_pos = window_manager.active_camera->get_view().getCenter();
    sprite.setPosition(camera_pos.x - window_manager.active_camera->get_view().getSize().x/2, camera_pos.y - window_manager.active_camera->get_view().getSize().y/2);
    window_manager.m_window.draw(sprite);

    //profiler.start("Display");
    window_manager.display();
    //profiler.stop("Display");
}

void sge::core::EngineCoreDebug::handle_debug_input() {
    if (input_manager.is_key_down(SGE_DEBUG_MAIN_KEY1) || input_manager.is_key_down(SGE_DEBUG_MAIN_KEY2)) {

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
}

bool sge::core::EngineCoreDebug::game_loop() {
    return EngineCore::game_loop();
}









