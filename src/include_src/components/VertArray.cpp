//
// Created by andrea on 5/21/19.
//

#include "SGE/components/graphics/VertArray.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"

sge::cmp::VertArray::VertArray(const utils::Handle<sge::GameObject> &_gameobject)
    : Component(_gameobject, "VertArray") {

    // Subscribing to the dirty_transform_event
    dirty_transform_handler = [&](){
        this->is_dirty = true;
        //std::cout << "Dirty Transform event" << std::endl;
    };

    gameobject()->transform()->transform_changed_event+= dirty_transform_handler;
}

void sge::cmp::VertArray::append_local_point(const sge::Vec2<float>& new_local_point) {
    m_local_points.push_back(new_local_point);
    auto new_world_point = Vec2<float>(0,0);
    m_vertex_array.append(sf::Vertex(sf::Vector2f(new_world_point.x, new_world_point.y)));
    is_dirty = true;
}

void sge::cmp::VertArray::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_vertex_array, states);
}

void sge::cmp::VertArray::destruction_callback() {
    IComponent::destruction_callback();
    if ( !gameobject()->get_scene()->env()->is_shutting_down())
        gameobject()->transform()->transform_changed_event -= dirty_transform_handler;
}

void sge::cmp::VertArray::clean_if_dirty() {
    if (is_dirty) {
        for (int i = 0; i < m_local_points.size(); ++i) {
            auto res_vec = gameobject()->transform()->local_to_world_point(m_local_points[i]);
            m_vertex_array[i].position = sf::Vector2f(res_vec.x, -res_vec.y);       // sge to sfml y-conversion
        }
        is_dirty = false;
    }
}

void sge::cmp::VertArray::set_primitive(sf::PrimitiveType primitive_type) {
    m_vertex_array.setPrimitiveType(primitive_type);
}

void sge::cmp::VertArray::set_color(sf::Color color) {
    for (int i = 0; i < m_vertex_array.getVertexCount(); ++i) {
        m_vertex_array[i].color = color;
    }
}



