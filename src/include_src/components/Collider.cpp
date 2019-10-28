#include <fstream>
#include "Collider.hpp"
#include "Scene.hpp"



sge::cmp::Collider::Collider(const utils::Handle<sge::GameObject>& _gameobject)
        : Component(_gameobject, "Collider") {

    auto this_handle = get_handle();
    relative_transform_changed_event = [=]() {
        this_handle->m_dirty_fixture_shape = true;
    };

    relative_hierarchy_changed_event = [=]() {
        this_handle->m_dirty_rigidbody = true;
    };

    clean_rigidbody();

    b2FixtureDef def;
    def.density = SGE_COLLIDER_DEFAULT_DENSITY;
    def.restitution = SGE_COLLIDER_DEFAULT_RESTITUTION;
    def.friction = SGE_COLLIDER_DEFAULT_FRICTION;

    b2CircleShape placeholder_shape;
    placeholder_shape.m_radius = 1.f;
    def.shape = &placeholder_shape;
    def.userData = this;

    m_fixture = m_rigidbody->get_b2_body()->CreateFixture(&def);
}



void sge::cmp::Collider::clean_shape() {

    switch (m_type) {

        case ColliderType::Polygon: {
            b2PolygonShape poly_shape;
            unsigned int count = m_path.get_size();
            b2Vec2 vertices[count];
            for (unsigned int i = 0; i < count; ++i) {
                auto res = Transform::change_reference_frame(gameobject()->transform(),
                                                             m_rigidbody->gameobject()->transform(), m_path[i]);
                vertices[i].Set(res.x*m_rigidbody->gameobject()->transform()->get_world_scale().x,
                                res.y*m_rigidbody->gameobject()->transform()->get_world_scale().y);
            }
            poly_shape.Set(vertices, count);
            poly_shape.m_centroid.SetZero();

            set_shape(&poly_shape);
            break;
        }

        case ColliderType::Circle: {
            b2CircleShape circle;
            circle.m_radius = m_radius;     // TODO apply transform
            set_shape(&circle);
            break;
        }
    }

    m_dirty_fixture_shape = false;
}

void sge::cmp::Collider::set_as_polygon(sge::Path path) {

    assert(path.is_closed());

    m_path = path;
    m_type = ColliderType ::Polygon;
    m_dirty_fixture_shape = true;
}

void sge::cmp::Collider::visual_debug_draw_collider() {
    auto rigidbody_transform = m_rigidbody->gameobject()->transform();

    switch (m_type) {

        case ColliderType::Polygon: {
            Path world_path;
            auto poly_shape = ((b2PolygonShape*)m_fixture->GetShape());
            for (int i = 0; i < poly_shape->m_count; ++i) {
                world_path.append_point(rigidbody_transform->local_to_world_point(Vec2<float>( poly_shape->m_vertices[i].x, poly_shape->m_vertices[i].y)));
            }
            world_path.append_point(rigidbody_transform->local_to_world_point(Vec2<float>( poly_shape->m_vertices[0].x, poly_shape->m_vertices[0].y)));
            gameobject()->get_scene()->env()->debug_draw_path(world_path);
            break;
        }
        case ColliderType::Circle: {
            gameobject()->get_scene()->env()->debug_draw_circle(gameobject()->transform()->get_world_position(), m_radius);
        }
    }

}

void sge::cmp::Collider::reallocation_callback() {
    // Update the b2Fixture userdata to reflect the new pointer of this collider
    m_fixture->SetUserData(this);
}

void sge::cmp::Collider::set_shape(b2Shape *shape) {
    b2FixtureDef def = clone_fixture_def(m_fixture);
    m_fixture->GetBody()->DestroyFixture(m_fixture);
    def.shape = shape;
    m_fixture = m_rigidbody->get_b2_body()->CreateFixture(&def);
}

b2FixtureDef sge::cmp::Collider::clone_fixture_def(b2Fixture *fixture) {
    b2FixtureDef def;
    def.shape = m_fixture->GetShape();
    def.density = m_fixture->GetDensity();
    def.restitution = m_fixture->GetRestitution();
    def.friction = m_fixture->GetFriction();
    def.isSensor = m_fixture->IsSensor();
    def.userData = m_fixture->GetUserData();
    return def;
}

void sge::cmp::Collider::clean_rigidbody() {
    update_upstream_handles();
    m_dirty_rigidbody = false;
}

void sge::cmp::Collider::clean_pass() {
    if (m_dirty_rigidbody) {
        clean_rigidbody();
    }
    if (m_dirty_fixture_shape) {
        clean_shape();
    }
}

void sge::cmp::Collider::update_upstream_handles() {

    for (int i = 0; i < relative_hierarchy_vector.size(); ++i) {
        relative_hierarchy_vector[i]->parent_changed_event.removeHandler(relative_hierarchy_changed_event);
        relative_hierarchy_vector[i]->local_transform_changed_event.removeHandler(relative_transform_changed_event);
    }

    relative_hierarchy_vector.clear();
    auto pointed_parent_transform = this->gameobject()->transform();
    while (!pointed_parent_transform.is_null()) {
        utils::Handle<Rigidbody> rigidbody = pointed_parent_transform->gameobject()->get_component<Rigidbody>("Rigidbody");
        if (rigidbody.is_valid()) {
            m_rigidbody = rigidbody;
            return;
        }
        else {
            relative_hierarchy_vector.push_back(pointed_parent_transform);
            pointed_parent_transform->parent_changed_event.addHandler(relative_hierarchy_changed_event);
            pointed_parent_transform->local_transform_changed_event.addHandler(relative_transform_changed_event);
        }
        pointed_parent_transform = pointed_parent_transform->get_parent();
    }
    LOG_ERROR << "Couldn't find a Rigidbody up the hierarchy";
    exit(1);
}

void sge::cmp::Collider::load_spath(const std::string &filename) {
    Path path;
    path.load_from_file(filename);
    set_as_polygon(path);

}

utils::Handle<sge::cmp::Rigidbody> sge::cmp::Collider::get_rigidbody() {
    return m_rigidbody;
}

void sge::cmp::Collider::set_sensor(bool is_sensor) {
    m_fixture->SetSensor(is_sensor);
}

bool sge::cmp::Collider::is_sensor() {
    return m_fixture->IsSensor();
}

void sge::cmp::Collider::set_as_circle(float radius) {
    m_radius = radius;
    m_type = ColliderType ::Circle;
    m_dirty_fixture_shape = true;
}

void sge::cmp::Collider::sed_restitution(float restitution) {
    m_fixture->SetRestitution(restitution);
}

void sge::cmp::Collider::set_friction(float friction) {
    m_fixture->SetFriction(friction);
}

void sge::cmp::Collider::set_density(float density) {
    m_fixture->SetDensity(density);
    m_rigidbody->get_b2_body()->ResetMassData();
}



