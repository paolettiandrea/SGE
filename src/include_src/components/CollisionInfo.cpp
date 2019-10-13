#include "CollisionInfo.hpp"
#include "PolygonCollider.hpp"

sge::Vec2<float> sge::CollisionInfo::get_my_velocity() {
    return m_my_velocity;
}

sge::Vec2<float> sge::CollisionInfo::get_its_velocity() {
    return m_its_velocity;
}

utils::Handle<sge::cmp::PolygonCollider> sge::CollisionInfo::get_my_collider() {
    return m_my_collider->get_handle();
}

utils::Handle<sge::cmp::PolygonCollider> sge::CollisionInfo::get_its_collider() {
    return m_its_collider->get_handle();
}

sge::CollisionInfo::CollisionInfo(sge::cmp::PolygonCollider *m_my_collider, sge::cmp::PolygonCollider *m_its_collider,
        const sge::Vec2<float> &m_my_velocity, const sge::Vec2<float> &m_its_velocity)
        : m_its_collider(m_its_collider), m_my_collider(m_my_collider), m_my_velocity(m_my_velocity),
          m_its_velocity(m_its_velocity) {}
