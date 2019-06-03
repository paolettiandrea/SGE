//
// Created by andrea on 6/2/19.
//

#include "SGE/components/physics/CircleCollider.hpp"

void sge::cmp::CircleCollider::clean_shape() {
    b2CircleShape shape;
    auto world_scale = gameobject()->transform()->get_world_scale();
    if (world_scale.x == world_scale.y) {
        shape.m_radius = m_radius*world_scale.x;
    } else {
        LOG_ERROR << "CircleColliders shouldn't be used when the scale for the two axis is different. \nworld_scale.x: "
                  << world_scale.x << ",  world_scale.y: " << world_scale.y;
        exit(1);
    }

    update_shape(&shape);
    m_dirty_fixture_shape = false;
}

void sge::cmp::CircleCollider::set_radius(float radius) {
    m_radius = radius;
    m_dirty_fixture_shape = true;
}

float sge::cmp::CircleCollider::get_radius() {
    return m_radius;
}

sge::cmp::CircleCollider::CircleCollider(const utils::Handle<sge::GameObject>& gameobject)
        : Collider(gameobject, "CircleCollider") {}
