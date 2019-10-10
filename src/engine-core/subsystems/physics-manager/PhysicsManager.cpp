#include "PhysicsManager.hpp"

sge::core::PhysicsManager::PhysicsManager(cd::PhysicsManager_ConstructionData data)
    : Subsystem("PHYSICS MANAGER")
    , m_rigidbody_component_creator("Rigidbody")
    , m_box_collider_component_creator("BoxCollider")
    , m_circle_collider_component_creator("CircleCollider")
    , m_polygon_collider_componet_creator("PolygonCollider")
    , m_fixed_delta_time(data.fixed_delta_time)
    {


    }

void sge::core::PhysicsManager::step(b2World& world) {
    LOG_DEBUG(35) << "Physics Step";
    world.Step(m_fixed_delta_time, 6, 2);
}

/**
 * \brief Updates all the position and rotations of the GameObjects with a Rigidbody in the active Scene according
 * to the simulated body's positions and rotation.
 */
void sge::core::PhysicsManager::dynamic_body_to_transform_update() {
    auto top_layer = m_rigidbody_component_creator.get_top_layer();
    for (auto rigidbody : top_layer->get_component_vector()) {
        if (rigidbody->m_body->GetType()==b2_dynamicBody)
            rigidbody->body_position_to_transform();
    }
}

void sge::core::PhysicsManager::kinematic_transform_to_body() {
    auto top_layer = m_rigidbody_component_creator.get_top_layer();
    for (auto rigidbody : top_layer->get_component_vector()) {
        if (rigidbody->m_body->GetType()==b2_kinematicBody)
            rigidbody->transform_to_body_position();
    }
}

void sge::core::PhysicsManager::collider_clean_pass() {
    for (auto box_collider : m_box_collider_component_creator.get_top_layer()->get_component_vector()) {
        box_collider->clean_pass();
    }

    for (auto circle_collider : m_circle_collider_component_creator.get_top_layer()->get_component_vector()) {
        circle_collider->clean_pass();
    }
    for (auto poly_collider : m_polygon_collider_componet_creator.get_top_layer()->get_component_vector()) {
        poly_collider->clean_pass();
    }
}

void sge::core::PhysicsManager::visual_debug_pass() {
    if (visual_debug_collider_switch) {
        for (auto circle_collider : m_circle_collider_component_creator.get_top_layer()->get_component_vector()) {
            circle_collider->visual_debug_draw_collider();
        }
        for (auto box_collider : m_box_collider_component_creator.get_top_layer()->get_component_vector()) {
            box_collider->visual_debug_draw_collider();
        }
        for (auto polygon_collider : m_polygon_collider_componet_creator.get_top_layer()->get_component_vector()) {
            polygon_collider->visual_debug_draw_collider();
        }
    }

}

void sge::core::PhysicsManager::toggle_visual_debug_collider() {
    visual_debug_collider_switch = !visual_debug_collider_switch;
    LOG_DEBUG(1) << "Toggled visual debug for Colliders -> " << visual_debug_collider_switch;
}

void sge::core::PhysicsManager::memory_buffer_pass() {
    m_box_collider_component_creator.memory_buffer_pass();
    m_circle_collider_component_creator.memory_buffer_pass();
    m_polygon_collider_componet_creator.memory_buffer_pass();
    m_rigidbody_component_creator.memory_buffer_pass();
}

void sge::core::PhysicsManager::update_active_world(b2World* world) {
    world->SetContactListener(&contactListener);
}



