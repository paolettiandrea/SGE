//
// Created by andrea on 6/16/19.
//

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
