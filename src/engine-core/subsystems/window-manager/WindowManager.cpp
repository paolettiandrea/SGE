//
// Created by andrea on 5/3/19.
//

#include "WindowManager.hpp"

using namespace sge::core;

WindowManager::WindowManager(const cd::WindowManager_ConstructionData &data)
    : Subsystem("WINDOW MANAGER")
    , m_window(sf::VideoMode(data.window_width, data.window_height), data.window_title)
    {
    m_window.setPosition(sf::Vector2i(data.window_pos_x, data.window_pos_y));
}

void WindowManager::handle_window_events() {
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}
