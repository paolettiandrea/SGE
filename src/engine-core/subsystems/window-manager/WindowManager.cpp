//
// Created by andrea on 5/3/19.
//

#include "WindowManager.hpp"

using namespace sge::core;

WindowManager::WindowManager(const cd::WindowManager_ConstructionData &data)
    : Subsystem("WINDOW MANAGER")
    , m_window(sf::VideoMode(data.window_width, data.window_height), data.window_title,sf::Style::Default, data.context_settings)
    , vertarray_component_creator("VertArray")
    , path_component_creator("PathRenderer")
    , m_camera(((float)data.window_width)/data.window_height, data.view_vertical_size)
    , m_render_states(sf::Transform::Identity)
    {
    m_window.setPosition(sf::Vector2i(data.window_pos_x, data.window_pos_y));
    m_window.setVerticalSyncEnabled(data.vsync_on);
    m_window.setView(m_camera.get_view());
}

void WindowManager::handle_window_events() {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // "close requested" event: close the window
        if (event.type == sf::Event::Closed)
            m_window.close();
    }

    // TEMP Just some temporary input to change the zoom
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Period)) {
        m_camera.add_zoom(10.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Comma)) {
        m_camera.add_zoom(-10.f);
    }

    // If some property of the camera has changed another setView is needed (since it makes an internal copy)
    if (m_camera.changed_view_flag) {
        m_window.setView(m_camera.m_view);
        m_camera.changed_view_flag = false;
    }
}

void WindowManager::draw() {
    for (auto vertarray : vertarray_component_creator.get_top_layer()->get_component_vector()) {
        vertarray->clean_if_dirty();
        m_window.draw(*vertarray.get_pointer(), m_render_states);
    }

    for (auto path : path_component_creator.get_top_layer()->get_component_vector()) {
        path->clean_pass();
        m_window.draw(*path.get_pointer(), m_render_states);
    }
}
