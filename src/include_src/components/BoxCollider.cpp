#include "BoxCollider.hpp"
#include "GameObject.hpp"
#include "Rigidbody.hpp"

sge::cmp::BoxCollider::BoxCollider(const utils::Handle<sge::GameObject>& gameobject)
: Collider(gameobject, "BoxCollider") {

}


void sge::cmp::BoxCollider::clean_shape() {

    b2PolygonShape shape;
    auto world_scale = gameobject()->transform()->get_world_scale();
    shape.SetAsBox(m_width/2*world_scale.x, m_height/2*world_scale.y);

    update_shape(&shape);
    m_dirty_fixture_shape = false;
}

void sge::cmp::BoxCollider::set_width(float width) {
    m_width = width;
    m_dirty_fixture_shape = true;
}

void sge::cmp::BoxCollider::set_height(float height) {
    m_height = height;
    m_dirty_fixture_shape = true;
}

float sge::cmp::BoxCollider::get_height() { return m_height; }

float sge::cmp::BoxCollider::get_width() { return m_width; }
