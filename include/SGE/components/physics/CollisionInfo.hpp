#ifndef SGE_COLLISIONINFO_HPP
#define SGE_COLLISIONINFO_HPP

#include "SGE/utils/handles/Handle.hpp"
#include "SGE/Vec2.hpp"

namespace sge{
    namespace cmp { class PolygonCollider; }
    class CollisionInfo {
    public:
        CollisionInfo(sge::cmp::PolygonCollider *m_my_collider,
                      sge::cmp::PolygonCollider *m_its_collider, const sge::Vec2<float> &m_my_velocity,
                      const sge::Vec2<float> &m_its_velocity);

    public:
        utils::Handle<sge::cmp::PolygonCollider> get_my_collider();
        utils::Handle<sge::cmp::PolygonCollider> get_its_collider();
        sge::Vec2<float> get_my_velocity();
        sge::Vec2<float> get_its_velocity();

    private:
        cmp::PolygonCollider* m_its_collider;
        cmp::PolygonCollider* m_my_collider;

        Vec2<float> m_my_velocity;
        Vec2<float> m_its_velocity;
    };
}



#endif //SGE_COLLISIONINFO_HPP
