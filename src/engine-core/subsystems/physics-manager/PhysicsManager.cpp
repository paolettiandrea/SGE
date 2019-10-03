#include "PhysicsManager.hpp"

sge::core::PhysicsManager::PhysicsManager(cd::PhysicsManager_ConstructionData data)
    : Subsystem("PHYSICS MANAGER")
    , m_rigidbody_component_creator("Rigidbody")
    , m_box_collider_component_creator("BoxCollider")
    , m_circle_collider_component_creator("CircleCollider")
    , m_polygon_collider_componet_creator("PolygonCollider")
    , m_fixed_delta_time(data.fixed_delta_time)
    {}

void sge::core::PhysicsManager::step(b2World& world) {
    LOG_DEBUG(35) << "Physics Step";
    world.Step(m_fixed_delta_time, 6, 2);
}

/**
 * \brief Updates all the position and rotations of the GameObjects with a Rigidbody in the active Scene according
 * to the simulated body's positions and rotation.
 */
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
