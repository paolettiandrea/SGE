#include <SGE/components/graphics/PathRenderer.hpp>
#include "PhysicsPolygon.hpp"
#include "SGE/components/physics/PolygonCollider.hpp"

std::string PhysicsPolygon::get_logic_type_id() {
    return "PhysicsPolygon";
}

void PhysicsPolygon::on_start() {
    Logic::on_start();
    auto path_renderer = gameobject()->add_component<sge::cmp::PathRenderer>("PathRenderer");
    path_renderer->set_path(m_path);
    path_renderer->set_thickness(0.1);

    auto rigidbody = gameobject()->add_component<sge::cmp::Rigidbody>("Rigidbody");
    auto poly_collider = gameobject()->add_component<sge::cmp::PolygonCollider>("PolygonCollider");
    poly_collider->set_path(m_path);
}

void PhysicsPolygon::on_collision_begin(sge::CollisionInfo &collision_info) {
    Logic::on_collision_begin(collision_info);
    LOG_INFO << "Begin collision with: " << collision_info.get_its_collider()->get_log_id() << "   \nmy speed: " << collision_info.get_my_velocity().to_string()
    << "\nits speed: " << collision_info.get_its_velocity().to_string();
}

void PhysicsPolygon::on_collision_end(sge::CollisionInfo &collision_info) {
    Logic::on_collision_end(collision_info);
    LOG_INFO << "End collision with: " << collision_info.get_its_collider()->get_log_id() << "   speed: " << collision_info.get_my_velocity().to_string();
}

void PhysicsPolygon::pre_solve(b2Contact *contact, const b2Manifold *oldManifold) {
    Logic::pre_solve(contact, oldManifold);
    LOG_INFO << "Pre solve";
    contact->SetEnabled(false);
}

void PhysicsPolygon::post_solve(b2Contact *contact, const b2ContactImpulse *impulse) {
    Logic::post_solve(contact, impulse);
    LOG_INFO << "Post solve";
}
