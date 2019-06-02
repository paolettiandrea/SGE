//
// Created by andrea on 5/28/19.
//

#ifndef FACTORY_EXPERIMENTS_PHYSICSMANAGER_HPP
#define FACTORY_EXPERIMENTS_PHYSICSMANAGER_HPP

#include "Subsystem.hpp"
#include "Rigidbody.hpp"
#include "BoxCollider.hpp"
#include "PhysicsManager_ConstructionData.hpp"
#include "Box2D/Box2D.h"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge::core {

    class PhysicsManager : public Subsystem {
    public:
        explicit PhysicsManager(cd::PhysicsManager_ConstructionData data);

        void clean_pass();
        void step(b2World& world);
        void update_transform();

        double fixed_delta_time() { return  m_fixed_delta_time; }

    private:
        ComponentCreator<cmp::Rigidbody> m_rigidbody_component_creator;
        ComponentCreator<cmp::BoxCollider> m_box_collider_component_creator;
        double m_fixed_delta_time;
    };
}

#endif //FACTORY_EXPERIMENTS_PHYSICSMANAGER_HPP
