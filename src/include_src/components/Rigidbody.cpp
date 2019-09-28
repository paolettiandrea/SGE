#include "SGE/components/physics/Rigidbody.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"

using sge::cmp::Rigidbody;

Rigidbody::Rigidbody(const utils::Handle<sge::GameObject>& _gameobject)
    : sge::cmp::Component<Rigidbody>( _gameobject, "Rigidbody") {
    b2BodyDef body_def;
    auto world_pos = gameobject()->transform()->get_world_position();
    body_def.position = b2Vec2(world_pos.x,world_pos.y);
    body_def.angle = gameobject()->transform()->get_world_rotation();
    body_def.type = b2_dynamicBody;
    auto world = gameobject()->get_scene()->get_b2World();
    m_body = world->CreateBody(&body_def);
}

void sge::cmp::Rigidbody::set_body_type(b2BodyType body_type) {
    m_body->SetType(body_type);
}

/**
 * \brief Updates this GameObject's position and rotation according to simulated body's position and rotation
 */
void sge::cmp::Rigidbody::update_transform() {
    auto position = m_body->GetPosition();
    gameobject()->transform()->set_local_position(position.x, position.y);
    auto rotation = m_body->GetAngle();
    gameobject()->transform()->set_local_rotation(rotation);
}

void sge::cmp::Rigidbody::destruction_callback() {
    IComponent::destruction_callback();
    if (!gameobject()->get_scene()->is_doomed()) {
        auto world = m_body->GetWorld();
        world->DestroyBody(m_body);
    }


}
