#include "SGE/components/physics/Rigidbody.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"

using sge::cmp::Rigidbody;

Rigidbody::Rigidbody(const GameObject_H& _gameobject)
    : sge::cmp::Component<Rigidbody>( _gameobject, "Rigidbody") {
    b2BodyDef body_def;
    auto world_pos = gameobject()->transform()->get_world_position();
    body_def.position = b2Vec2(world_pos.x,world_pos.y);
    body_def.angle = gameobject()->transform()->get_world_rotation();
    body_def.type = b2_dynamicBody;
    auto world = gameobject()->get_scene()->get_b2World();
    m_body = world->CreateBody(&body_def);

    auto handle = get_handle();
    transform_changed_callback = [=]() {
        handle->dirty_body_position_flag = true;
    };


}

void sge::cmp::Rigidbody::set_body_type(b2BodyType body_type) {
    if (body_type!=m_body->GetType()){

        // If the body WAS a kinematic one, unsubscribe from the transform changed event (no need to update the body position anymore)
        if (m_body->GetType()==b2BodyType::b2_kinematicBody) {
            gameobject()->transform()->world_transform_changed_event.removeHandler(transform_changed_callback);
        }

        m_body->SetType(body_type);

        // If the body NOW IS a kinematic one, we need to subscribe to the transform changed event
        if (m_body->GetType()==b2BodyType::b2_kinematicBody) {
            gameobject()->transform()->world_transform_changed_event.addHandler(transform_changed_callback);
            transform_to_body_position();
        }
    }
}

/**
 * \brief Updates this GameObject's position and rotation according to simulated body's position and rotation
 */
void sge::cmp::Rigidbody::body_position_to_transform() {
    auto body_position = sge::Vec2<float>(m_body->GetPosition().x, m_body->GetPosition().y);
    auto transform_position = gameobject()->transform()->get_local_position();
    if (body_position!= transform_position) {
        gameobject()->transform()->set_local_position(body_position);
    }

    auto body_rotation = m_body->GetAngle();
    if (body_rotation!=gameobject()->transform()->get_local_rotation()){
        gameobject()->transform()->set_local_rotation(body_rotation);
    }
}

void sge::cmp::Rigidbody::destruction_callback() {
    IComponent::destruction_callback();
    if (!gameobject()->get_scene()->is_doomed()) {
        auto world = m_body->GetWorld();
        world->DestroyBody(m_body);
        if (m_body->GetType()==b2_kinematicBody)
            gameobject()->transform()->world_transform_changed_event.removeHandler(transform_changed_callback);

    }

    }


void sge::cmp::Rigidbody::transform_to_body_position() {
    auto pos = gameobject()->transform()->get_world_position();
    auto rot = gameobject()->transform()->get_world_rotation();
    m_body->SetTransform(b2Vec2(pos.x, pos.y), rot);
}

void sge::cmp::Rigidbody::apply_force(sge::Vec2<float> force_vec, sge::Vec2<float> apply_pos, bool wake) {
    m_body->ApplyForce(b2Vec2(force_vec.x, force_vec.y), b2Vec2(apply_pos.x, apply_pos.y), wake);
}

void sge::cmp::Rigidbody::apply_force_center(sge::Vec2<float> force_vec, bool wake) {
    m_body->ApplyForceToCenter(b2Vec2(force_vec.x, force_vec.y), wake);
}

void sge::cmp::Rigidbody::apply_torque(float torque, bool wake) {
    m_body->ApplyTorque(torque, wake);
}

void sge::cmp::Rigidbody::apply_angular_impulse(float impulse, bool wake) {
    m_body->ApplyAngularImpulse(impulse, wake);
}

void sge::cmp::Rigidbody::apply_linear_impulse(const Vec2<float> &impulse_vec, const Vec2<float> &impulse_point, bool wake) {
    m_body->ApplyLinearImpulse(b2Vec2(impulse_vec.x, impulse_vec.y), b2Vec2(impulse_point.x, impulse_point.y), wake);
}

void sge::cmp::Rigidbody::set_fixed_rotation(bool fixed_rotation) {
    m_body->SetFixedRotation(fixed_rotation);
}

float sge::cmp::Rigidbody::get_mass() {
    return m_body->GetMass();
}

void sge::cmp::Rigidbody::set_transform(const sge::Vec2<float>& position, float rotation) {
    if (m_body!= nullptr) {
        m_body->SetTransform(b2Vec2(position.x, position.y), rotation);
    } else {
        LOG_ERROR << "m_body == nullptr";
        exit(1);
    }
}

std::string sge::cmp::Rigidbody::get_debug_string() {
    auto s = IComponent::get_debug_string();

    s += "Body type: ";
    switch (m_body->GetType()) {

        case b2_staticBody:
            s += "STATIC";
            break;
        case b2_kinematicBody:
            s += "KINEMATIC";
            break;
        case b2_dynamicBody:
            s += "DYNAMIC";
            break;
    }
    s += "\n";

    s += "Mass: " + std::to_string(get_mass()) + "\n";
    s += "Linear vel: " + std::to_string(m_body->GetLinearVelocity().Length()) + "\n";
    s += "Angular vel: " + std::to_string(m_body->GetAngularVelocity()) + "\n";
    s += "Fixed rotation: " + std::to_string(m_body->IsFixedRotation()) + "\n";
    s += "Is bullet: " + std::to_string(m_body->IsBullet()) + "";

    return s;
}

sge::Vec2<float> sge::cmp::Rigidbody::get_linear_velocity() {
    auto b2vel = m_body->GetLinearVelocity();
    return sge::Vec2<float>(b2vel.x, b2vel.y);
}


