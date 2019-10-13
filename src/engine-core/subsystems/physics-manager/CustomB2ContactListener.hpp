#ifndef SGE_CUSTOMB2CONTACTLISTENER_HPP
#define SGE_CUSTOMB2CONTACTLISTENER_HPP

#include <vector>
#include <SGE/components/physics/PolygonCollider.hpp>
#include "Box2D/Box2D.h"
namespace sge::cmp {
    class CustomB2ContactListener : public b2ContactListener {
    public:


        void BeginContact(b2Contact *contact) override;

        void EndContact(b2Contact *contact) override;

        void trigger_collision_callbacks();

        void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

        void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) override;

    private:
        std::vector<sge::CollisionInfo> m_begin_collision_info_buffer;
        std::vector<sge::CollisionInfo> m_end_collision_info_buffer;

    };
}



#endif //SGE_CUSTOMB2CONTACTLISTENER_HPP
