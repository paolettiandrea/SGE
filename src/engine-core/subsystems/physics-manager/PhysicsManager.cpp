#include "PhysicsManager.hpp"

sge::core::PhysicsManager::PhysicsManager(cd::PhysicsManager_ConstructionData data)
    : Subsystem("PHYSICS MANAGER")
    , m_rigidbody_component_creator("Rigidbody")
    , m_box_collider_component_creator("BoxCollider")
    , m_circle_collider_component_creator("CircleCollider")
    , m_fixed_delta_time(data.fixed_delta_time)
    {

    }

void sge::core::PhysicsManager::step(b2World& world) {
    LOG_DEBUG(35) << "Physics Step";
    world.Step(m_fixed_delta_time, 6, 2);
}

void sge::core::PhysicsManager::update_transform() {
    auto top_layer = m_rigidbody_component_creator.get_top_layer();
    for (auto rigidbody : top_layer->get_component_vector()) {
        rigidbody->update_transform();
    }
}

void sge::core::PhysicsManager::clean_pass() {
    for (auto box_collider : m_box_collider_component_creator.get_top_layer()->get_component_vector()) {
        box_collider->clean_pass();
    }

    for (auto circle_collider : m_circle_collider_component_creator.get_top_layer()->get_component_vector()) {
        circle_collider->clean_pass();
    }
}
