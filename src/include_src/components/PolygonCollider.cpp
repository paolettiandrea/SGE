#include "PolygonCollider.hpp"
#include "Scene.hpp"


sge::cmp::PolygonCollider::PolygonCollider(const utils::Handle<sge::GameObject>& _gameobject)
        : Component(_gameobject, "PolygonCollider") {
    clean_rigidbody();

    b2FixtureDef def;
    def.density = SGE_COLLIDER_DEFAULT_DENSITY;
    def.restitution = SGE_COLLIDER_DEFAULT_RESTITUTION;
    def.friction = SGE_COLLIDER_DEFAULT_FRICTION;

    b2CircleShape placeholder_shape;
    placeholder_shape.m_radius = 1.f;
    def.shape = &placeholder_shape;
    def.userData = this;        // REMEMBER THAT THIS POINTER NEEDS TO BE UPDATED AFTER A REALLOCATION

    m_fixture = m_rigidbody->get_b2_body()->CreateFixture(&def);
}

void sge::cmp::PolygonCollider::clean_shape() {
    b2PolygonShape poly_shape;

    b2Vec2 vertices[m_path.get_size()];
    for (unsigned int i = 0; i < m_path.get_size(); ++i) {
        auto res = Transform::change_reference_frame(gameobject()->transform(),
                m_rigidbody->gameobject()->transform(), m_path[i]);
        vertices[i].Set(res.x*m_rigidbody->gameobject()->transform()->get_world_scale().x,
                res.y*m_rigidbody->gameobject()->transform()->get_world_scale().y);
    }
    poly_shape.Set(vertices, m_path.get_size());
    poly_shape.m_centroid.SetZero();

    set_shape(&poly_shape);

    m_dirty_fixture_shape = false;
}

void sge::cmp::PolygonCollider::set_path(sge::Path path) {
    m_path = path;
    m_dirty_fixture_shape = true;
}

void sge::cmp::PolygonCollider::visual_debug_draw_collider() {
    Path world_path;
    for (int i = 0; i < m_path.get_size(); ++i) {
        world_path.append_point(gameobject()->transform()->local_to_world_point(m_path[i]));
    }
    gameobject()->get_scene()->env()->debug_draw_path(world_path);
}

void sge::cmp::PolygonCollider::reallocation_callback() {
    // Update the b2Fixture userdata to reflect the new pointer of this collider
    m_fixture->SetUserData(this);
}

void sge::cmp::PolygonCollider::set_shape(b2Shape *shape) {
    b2FixtureDef def = clone_fixture_def(m_fixture);
    m_fixture->GetBody()->DestroyFixture(m_fixture);
    def.shape = shape;
    m_fixture = m_rigidbody->get_b2_body()->CreateFixture(&def);
}

b2FixtureDef sge::cmp::PolygonCollider::clone_fixture_def(b2Fixture *fixture) {
    b2FixtureDef def;
    def.shape = m_fixture->GetShape();
    def.density = m_fixture->GetDensity();
    def.restitution = m_fixture->GetRestitution();
    def.friction = m_fixture->GetFriction();
    def.isSensor = m_fixture->IsSensor();
    def.userData = m_fixture->GetUserData();
    return def;
}

void sge::cmp::PolygonCollider::clean_rigidbody() {
    m_rigidbody = find_rigidbody_upstream();
    if (m_rigidbody.is_valid()) {
        m_dirty_rigidbody = false;
    } else {
        LOG_ERROR << "Couldn't find a Rigidbody up the hierarchy";
        exit(1);
    }
}

void sge::cmp::PolygonCollider::clean_pass() {
    if (m_dirty_rigidbody) {
        clean_rigidbody();
    }
    if (m_dirty_fixture_shape) {
        clean_shape();
    }
}

utils::Handle<sge::cmp::Rigidbody> sge::cmp::PolygonCollider::find_rigidbody_upstream() {
    auto pointed_parent_transform = this->gameobject()->transform();
    while (!pointed_parent_transform.is_null()) {
        utils::Handle<Rigidbody> rigidbody = pointed_parent_transform->gameobject()->template get_component<Rigidbody>("Rigidbody");
        if (rigidbody.is_valid()) return rigidbody;
        pointed_parent_transform = pointed_parent_transform->get_parent();
    }
    return utils::Handle<Rigidbody>::null();
}



