//
// Created by andrea on 6/2/19.
//

#include <SGE/components/graphics/PathRenderer.hpp>
#include <SGE/components/physics/CircleCollider.hpp>
#include "PhysicsCircle.hpp"
#include "SGE/components/physics/Rigidbody.hpp"

std::string PhysicsCircle::get_logic_type_id() {
    return "PhysicsCircle";
}

void PhysicsCircle::on_start() {
    Logic::on_start();
    using namespace sge;
    //auto rigidbody = gameobject()->add_component<cmp::Rigidbody>("Rigidbody");
    auto collider = gameobject()->add_component<cmp::CircleCollider>("CircleCollider");
    collider->set_radius(1.f);

    auto path_renderer = gameobject()->add_component<cmp::PathRenderer>("PathRenderer");
    path_renderer->set_path_as_circle(1.f, 10);
    path_renderer->set_thickness(0.1f);
}

void PhysicsCircle::on_update() {
    Logic::on_update();

}


