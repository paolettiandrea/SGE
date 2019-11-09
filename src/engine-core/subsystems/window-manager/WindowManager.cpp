#include "WindowManager.hpp"

using namespace sge::core;

WindowManager::WindowManager(const cd::WindowManager_ConstructionData &data)
    : Subsystem("WINDOW MANAGER")
    , m_window(sf::VideoMode(data.window_width, data.window_height), data.window_title,sf::Style::Default, data.context_settings)
    , vertarray_component_creator("VertArray")
    , path_component_creator("PathRenderer")
    , m_render_states(sf::Transform::Identity)
    {
    m_window.setPosition(sf::Vector2i(data.window_pos_x, data.window_pos_y));
    m_window.setVerticalSyncEnabled(data.vsync_on);

    layer_count = data.layers.size();
    if (layer_count<=0) {
        LOG_ERROR << "There must be at least one layer!";
        exit(1);
    }
    for (unsigned int i = 0; i < data.layers.size(); ++i) {
        if (layers_map.count(data.layers[i])==0) {
            layers_map[data.layers[i]] = i;
        } else {
            LOG_ERROR << "The string [" << data.layers[i] << "was used to define more than one layer";
            exit(1);

        }
    }
}

void WindowManager::prepare_render() {


    // If some property of the camera has changed another setView is needed (since it makes an internal copy)
    if (active_camera->changed_view_flag) {
        m_window.setView(active_camera->m_view);
        active_camera->changed_view_flag = false;
    }
}

void WindowManager::draw() {

    // Divide the vertarrays based on the layer and draw them in order
    std::vector<sge::cmp::VertArray*> ordered_pointers[layer_count];
    for (auto vertarray : vertarray_component_creator.get_top_layer()->get_component_vector()) {
        if (vertarray->is_active()){
            vertarray->clean_layer_index_if_dirty(layers_map);
            vertarray->clean_if_dirty();
            ordered_pointers[vertarray->layer_index].push_back(vertarray.get_pointer());
        }
    }
    for (int i = layer_count-1; i >= 0; i--) {
        for (int j = 0; j < ordered_pointers[i].size(); ++j) {
            m_window.draw(*ordered_pointers[i][j], m_render_states);
        }
    }


    // TODO remove path component entirely
    for (auto path : path_component_creator.get_top_layer()->get_component_vector()) {
        if (path->is_active()){
            path->clean_pass();
            m_window.draw(*path.get_pointer(), m_render_states);
        }
    }
}

void WindowManager::visual_debug_pass() {
    if (visual_debug_path_switch) {
        for (auto path_renderer : path_component_creator.get_top_layer()->get_component_vector()) {
            path_renderer->visual_debug_draw_path();
        }
    }

    if (visual_debug_triangle_strip_switch) {
        for (auto path_renderer : path_component_creator.get_top_layer()->get_component_vector()) {
            path_renderer->visual_debug_draw_triangle_strip();
        }
    }
}

void WindowManager::update_camera_ratio() {
    active_camera->set_ratio(((float)m_window.getSize().x) / m_window.getSize().y);
}

void WindowManager::update_active_camera(sge::Camera *new_active_camera) {
    active_camera = new_active_camera;
    update_camera_ratio();
    m_window.setView(active_camera->get_view());
}

void WindowManager::memory_buffer_pass() {
    path_component_creator.memory_buffer_pass();
    vertarray_component_creator.memory_buffer_pass();
}

