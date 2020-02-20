#ifndef SGE_PHYSICSMANAGER_HPP
#define SGE_PHYSICSMANAGER_HPP

#include "Collider.hpp"
#include "Subsystem.hpp"
#include "Rigidbody.hpp"
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

        void trigger_collision_callbacks();

        int get_collision_layer_index_from_id(const std::string &id);

    private:
        ComponentCreator<cmp::Rigidbody> m_rigidbody_component_creator;
        ComponentCreator<cmp::Collider> m_collider_componet_creator;
        double m_fixed_delta_time;

        cmp::CustomB2ContactListener contactListener;

        bool visual_debug_collider_switch = false;

        std::vector<std::string> collision_layer_ids;
    };



}

#endif //SGE_PHYSICSMANAGER_HPP
