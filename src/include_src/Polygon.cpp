#include "Polygon.hpp"
#include <math.h>       /* sin */
#include "GameObject.hpp"

#define PI 3.14159265

using sge::cmp::Polygon;
using utils::Handle;

Polygon::Polygon(const Handle<GameObject> &gameobject)
    : Component(gameobject, "Polygon") {
    m_vertex_array.setPrimitiveType(sf::TriangleFan);
}

void sge::cmp::Polygon::set_polygon(float radius, int vertices_number) {
    m_vertex_array.clear();
    m_vert_number = vertices_number;
    double angle = 2*PI / vertices_number;
    for (int i = 0; i < vertices_number; ++i) {
        m_vertex_array.append(sf::Vertex(sf::Vector2f(sin(angle*i)*radius, cos(angle*i)*radius)));
    }
}


void sge::cmp::Polygon::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= m_gap_transform;
        target.draw(m_vertex_array, states);

}

void sge::cmp::Polygon::update_gap_transform() {
    auto my_transform = this->gameobject()->transform();
    m_gap_transform = sf::Transform::Identity;
    m_gap_transform.translate(my_transform->get_world_position().x,
                              my_transform->get_world_position().y);
    m_gap_transform.rotate(my_transform->get_world_rotation());
    m_gap_transform.scale(my_transform->get_world_scale(),my_transform->get_world_scale());
}


