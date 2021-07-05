#include <SGE/components/physics/PolygonCollider.hpp>
#include "StaticPolygon.hpp"
#include "PhysicsPolygon.hpp"

std::string StaticPolygon::get_logic_type_id() {
    return "StaticPolygon";
}

void StaticPolygon::on_start() {
    gameobject()->logichub()->attach_logic(new PhysicsPolygon(path));

    auto poly_collider = gameobject()->get_component<sge::cmp::Rigidbody>("Rigidbody");
    poly_collider->set_body_type(b2_staticBody);
}
