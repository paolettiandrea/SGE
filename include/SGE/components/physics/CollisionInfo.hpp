#ifndef SGE_COLLISIONINFO_HPP
#define SGE_COLLISIONINFO_HPP

#include "SGE/utils/handles/Handle.hpp"
#include "SGE/Vec2.hpp"
#include <Box2D/Box2D.h>
#include "SGE/utils/events/Events.hpp"

namespace sge{
    namespace cmp { class Collider; }

    class CollisionInfo {
    public:
        CollisionInfo(sge::cmp::Collider *m_my_collider,
                      sge::cmp::Collider *m_its_collider, const sge::Vec2<float> &m_my_velocity,
                      const sge::Vec2<float> &m_its_velocity);


    public:

        sge::Vec2<float> get_impact_velocity() const;
        utils::Handle<cmp::Collider> m_its_collider;

        utils::Handle<cmp::Collider> m_my_collider;

        Vec2<float> m_my_velocity;

        Vec2<float> m_its_velocity;

    };
}



#endif //SGE_COLLISIONINFO_HPP
