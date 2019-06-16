#include "SGE/components/physics/CircleCollider.hpp"
#include "SGE/Scene.hpp"

void sge::cmp::CircleCollider::clean_shape() {

    b2CircleShape shape;
    // TEMP reversing the Transform doesn't work yet TODO
    auto relative_position = Transform::change_reference_frame(gameobject()->transform(), m_rigidbody->gameobject()->transform(), m_local_center_offset);
    shape.m_p.Set(relative_position.x, relative_position.y);

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
        : Collider(gameobject, "CircleCollider") {

}

void sge::cmp::CircleCollider::set_center_offset(sge::Vec2<float> new_pos) {
    m_local_center_offset = new_pos;
    m_dirty_fixture_shape = true;
}

sge::Vec2<float> sge::cmp::CircleCollider::get_center_offset() { return  m_local_center_offset; }

void sge::cmp::CircleCollider::visual_debug_pass() {
    gameobject()->get_scene()->env()->debug_draw_circle(gameobject()->transform()->local_to_world_point(m_local_center_offset),m_radius*gameobject()->transform()->get_world_scale().x,0.f,"",0);
}
