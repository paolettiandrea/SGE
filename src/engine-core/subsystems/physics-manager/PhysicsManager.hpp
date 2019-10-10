#ifndef SGE_PHYSICSMANAGER_HPP
#define SGE_PHYSICSMANAGER_HPP

#include "CircleCollider.hpp"
#include "PolygonCollider.hpp"
#include "Subsystem.hpp"
#include "Rigidbody.hpp"
#include "BoxCollider.hpp"
#include "PhysicsManager_ConstructionData.hpp"
#include "Box2D/Box2D.h"
#include "CustomB2ContactListener.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge::core {



    class PhysicsManager : public Subsystem {
    public:
        explicit PhysicsManager(cd::PhysicsManager_ConstructionData data);

        void collider_clean_pass();
        void step(b2World& world);
        void dynamic_body_to_transform_update();
        void kinematic_transform_to_body();

        double fixed_delta_time() { return  m_fixed_delta_time; }

        void visual_debug_pass() override;

        void toggle_visual_debug_collider();

        void memory_buffer_pass() override;

        void update_active_world(b2World* world);

    private:
        ComponentCreator<cmp::Rigidbody> m_rigidbody_component_creator;
        ComponentCreator<cmp::BoxCollider> m_box_collider_component_creator;
        ComponentCreator<cmp::CircleCollider> m_circle_collider_component_creator;
        ComponentCreator<cmp::PolygonCollider> m_polygon_collider_componet_creator;
        double m_fixed_delta_time;

        cmp::CustomB2ContactListener contactListener;

        bool visual_debug_collider_switch = false;
    };




}

#endif //SGE_PHYSICSMANAGER_HPP
