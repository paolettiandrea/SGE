#include "PolygonCollider.hpp"
#include "Scene.hpp"

sge::cmp::PolygonCollider::PolygonCollider(const utils::Handle<sge::GameObject>& _gameobject)
        : Collider(_gameobject, "PolygonCollider") {}

void sge::cmp::PolygonCollider::clean_shape() {
    b2PolygonShape poly_shape;

    b2Vec2 vertices[m_path.get_size()];
    for (int i = 0; i < m_path.get_size(); ++i) {
        auto res = Transform::change_reference_frame(gameobject()->transform(),
                m_rigidbody->gameobject()->transform(), m_path[i]);
        vertices[i].Set(res.x*m_rigidbody->gameobject()->transform()->get_world_scale().x,
                res.y*m_rigidbody->gameobject()->transform()->get_world_scale().y);
    }
    poly_shape.Set(vertices, m_path.get_size());
    poly_shape.m_centroid.SetZero();

    set_shape(&poly_shape);

    m_dirty_fixture_shape = false;
}

void sge::cmp::PolygonCollider::set_path(sge::Path path) {
    m_path = path;
    m_dirty_fixture_shape = true;
}

void sge::cmp::PolygonCollider::visual_debug_draw_collider() {
    Path world_path;
    for (int i = 0; i < m_path.get_size(); ++i) {
        world_path.append_point(gameobject()->transform()->local_to_world_point(m_path[i]));
    }
    gameobject()->get_scene()->env()->debug_draw_path(world_path);
}



