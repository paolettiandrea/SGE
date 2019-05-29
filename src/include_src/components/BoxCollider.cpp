//
// Created by andrea on 5/28/19.
//

#include "BoxCollider.hpp"
#include "GameObject.hpp"
#include "Rigidbody.hpp"

sge::cmp::BoxCollider::BoxCollider(const utils::Handle<sge::GameObject>& gameobject)
: Component(gameobject, "BoxCollider") {}

void sge::cmp::BoxCollider::initialize(float width, float height) {
    auto rigidbody = gameobject()->get_component<sge::cmp::Rigidbody>("Rigidbody");
    if (rigidbody.is_valid()) {
        b2FixtureDef fixture_def;
        b2PolygonShape box_shape;
        box_shape.SetAsBox(width/2, height/2);
        fixture_def.shape = &box_shape;
        fixture_def.density = 1.0f;
        fixture_def.friction = 0.3f;
        fixture_def.restitution = 1;
        auto m_fixture = rigidbody->get_b2_body()->CreateFixture(&fixture_def);
    } else {
        LOG_WARNING << "No Rigidbody found on this gameobject";

    }
}
