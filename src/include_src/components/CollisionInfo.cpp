#include "CollisionInfo.hpp"
#include "Collider.hpp"

sge::CollisionInfo::CollisionInfo(sge::cmp::Collider *m_my_collider, sge::cmp::Collider *m_its_collider,
                                  const sge::Vec2<float> &m_my_velocity, const sge::Vec2<float> &m_its_velocity)
        : m_its_collider(m_its_collider->get_handle()), m_my_collider(m_my_collider->get_handle()), m_my_velocity(m_my_velocity),
          m_its_velocity(m_its_velocity) {

}

sge::Vec2<float> sge::CollisionInfo::get_impact_velocity() const {
    return m_my_velocity-m_its_velocity;
}

