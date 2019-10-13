//
// Created by andrea on 6/16/19.
//

#ifndef SGE_PHYSICSPOLYGON_HPP
#define SGE_PHYSICSPOLYGON_HPP

#include "SGE/logic/Logic.hpp"
/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class PhysicsPolygon : public sge::Logic  {
public:
    PhysicsPolygon(sge::Path path) : m_path(path) {}


    std::string get_logic_type_id() override;

    void on_start() override;

    void on_collision_begin(sge::CollisionInfo &collision_info) override;

    void on_collision_end(sge::CollisionInfo &collision_info) override;

    void pre_solve(b2Contact *contact, const b2Manifold *oldManifold) override;

    void post_solve(b2Contact *contact, const b2ContactImpulse *impulse) override;

private:
    sge::Path m_path;

};


#endif //SGE_PHYSICSPOLYGON_HPP
