#include <fstream>
#include "Collider.hpp"
#include "Scene.hpp"


sge::cmp::Collider::Collider(const GameObject_H& _gameobject)
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

    gameobject()->transform()->parent_changed_event += relative_transform_changed_event;

}


void sge::cmp::Collider::clean_shape() {

    switch (m_type) {

        case ColliderType::Polygon: {
            b2PolygonShape poly_shape;
            unsigned int count = m_path.get_size();
            b2Vec2 vertices[count];
            update_relative_path();
            for (unsigned int i = 0; i < count; ++i) {
                vertices[i].Set(m_relative_path[i].x,m_relative_path[i].y);
            }
            poly_shape.Set(vertices, count);
            poly_shape.m_centroid.SetZero();

            set_shape(&poly_shape);
            break;
        }

        case ColliderType::Circle: {
            b2CircleShape circle;
            auto scale = gameobject()->transform()->get_world_scale();
            if (scale.x == scale.y) {
                circle.m_radius = m_radius * scale.x;
                set_shape(&circle);
            } else {
                LOG_ERROR << "Doesn't make a sense to have a Circle Collider in an object with different scaling for x and y axis";
                exit(1);
            }
            break;
        }

        case Chain:
            b2Vec2 vs[m_path.get_closed_size()];
            update_relative_path();
            for (int i = 0; i < m_relative_path.get_size(); i++) {
                auto yo = gameobject()->transform()->local_to_world_point(m_path[i]);
                vs[i].Set(yo.x, yo.y);
            }
            if (m_path.is_closed()) {
                vs[m_path.get_closed_size() - 1] = vs[0];
            }
            b2ChainShape chain_shape;
            chain_shape.CreateChain(vs, m_path.get_closed_size());
            set_shape(&chain_shape);
            break;
    }

    m_dirty_fixture_shape = false;
}

void sge::cmp::Collider::set_as_polygon(sge::Path path) {

    if (!path.is_closed())
        path.set_closed(true);

    m_path = path;
    m_type = ColliderType::Polygon;
    m_dirty_fixture_shape = true;
}

void sge::cmp::Collider::visual_debug_draw_collider() {
    auto rigidbody_transform = m_rigidbody->gameobject()->transform();

    switch (m_type) {

        case ColliderType::Polygon: {
            Path world_path;
            auto poly_shape = ((b2PolygonShape*)m_fixture->GetShape());
            for (int i = 0; i < poly_shape->m_count; ++i) {
                world_path.append_point(rigidbody_transform->local_to_world_point(Vec2<float>( poly_shape->m_vertices[i].x/rigidbody_transform->get_world_scale().x, poly_shape->m_vertices[i].y/rigidbody_transform->get_world_scale().y)));
            }
            world_path.append_point(rigidbody_transform->local_to_world_point(Vec2<float>( poly_shape->m_vertices[0].x/rigidbody_transform->get_world_scale().x, poly_shape->m_vertices[0].y/rigidbody_transform->get_world_scale().y)));
            gameobject()->get_scene()->env()->debug_draw_path(world_path);
            break;
        }
        case ColliderType::Circle: {
            gameobject()->get_scene()->env()->debug_draw_circle(gameobject()->transform()->get_world_position(), m_radius*gameobject()->transform()->get_world_scale().x);
            break;
        }

        case Chain:
            Path world_path;
            auto chain_shape = ((b2ChainShape*)m_fixture->GetShape());
            for (int j = 0; j < m_path.get_size(); ++j) {
                world_path.append_point(rigidbody_transform->local_to_world_point(m_path[j]));
            }
            if (m_path.is_closed()) world_path.set_closed(true);
            gameobject()->get_scene()->env()->debug_draw_path(world_path);
            break;
    }

}

void sge::cmp::Collider::destruction_callback() {
    IComponent::destruction_callback();
    if (!gameobject()->get_scene()->is_doomed() && !get_rigidbody()->gameobject()->is_doomed()) {
        get_rigidbody()->get_b2_body()->DestroyFixture(m_fixture);
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
    def.shape = fixture->GetShape();
    def.density = fixture->GetDensity();
    def.restitution = fixture->GetRestitution();
    def.friction = fixture->GetFriction();
    def.isSensor = fixture->IsSensor();
    def.userData = fixture->GetUserData();
    def.filter = fixture->GetFilterData();
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

Rigidbody_H sge::cmp::Collider::get_rigidbody() {
    return m_rigidbody;
}

void sge::cmp::Collider::set_sensor(bool is_sensor) {
    m_fixture->SetSensor(is_sensor);

    if (is_sensor) {
        previous_density = m_fixture->GetDensity();
        m_fixture->SetDensity(0.0000001);
    } else {
        if (previous_density != -1) {
            m_fixture->SetDensity(previous_density);
        } else {
            LOG_ERROR << "No previous density!";
        }
    }
}

bool sge::cmp::Collider::is_sensor() {
    return m_fixture->IsSensor();
}

void sge::cmp::Collider::set_as_circle(float radius) {
    m_radius = radius;
    m_type = ColliderType ::Circle;
    m_dirty_fixture_shape = true;
}

void sge::cmp::Collider::set_restitution(float restitution) {
    m_fixture->SetRestitution(restitution);
}

void sge::cmp::Collider::set_friction(float friction) {
    m_fixture->SetFriction(friction);
}

void sge::cmp::Collider::set_density(float density) {
    m_fixture->SetDensity(density);
    m_rigidbody->get_b2_body()->ResetMassData();
}

void sge::cmp::Collider::set_as_chain(sge::Path path) {
    m_path = path;
    m_type = ColliderType::Chain;
    m_dirty_fixture_shape = true;
}

void sge::cmp::Collider::update_relative_path() {
    m_relative_path.clear();
    for (int i = 0; i < m_path.get_size(); ++i) {
        auto res = Transform::change_reference_frame(gameobject()->transform(),
                                                     m_rigidbody->gameobject()->transform(), m_path[i]);
        m_relative_path.append_point(sge::Vec2<float>(res.x*m_rigidbody->gameobject()->transform()->get_world_scale().x,
                                                      res.y*m_rigidbody->gameobject()->transform()->get_world_scale().y));
    }

}

std::string sge::cmp::Collider::get_debug_string() {
    auto s =  IComponent::get_debug_string();

    s += "Type: ";
    switch (m_type) {

        case Polygon:
            s += "POLYGON\n";
            s += "Points: " + std::to_string(m_path.get_size()) + "";
            break;
        case Circle:
            s += "CIRCLE\n";
            s += "Radius: " + std::to_string(m_radius) + "";
            break;
        case Chain:
            s += "CHAIN\n";
            s += "Points: " + std::to_string(m_path.get_size()) + "";
            break;
    }

    return s;
}

void sge::cmp::Collider::set_collision_category(const std::string &id) {
    int index = gameobject()->get_scene()->env()->get_collision_layer_index_from_id(id);

    if (index>=0 && index < 16) {
        b2Filter filter(m_fixture->GetFilterData());

        filter.categoryBits = 1<<index;

        m_fixture->SetFilterData(filter);
    } else {
        LOG_ERROR << "Couldn't find the collision layer id: " << id;
        exit(1);
    }

}

void sge::cmp::Collider::set_collision_enabled_with(const std::string &id, bool enabled) {
    int index = gameobject()->get_scene()->env()->get_collision_layer_index_from_id(id);

    if (index>=0 && index < 16) {
        b2Filter filter(m_fixture->GetFilterData());

        if (enabled) filter.maskBits = filter.maskBits | (1<<index);
        else filter.maskBits = filter.maskBits & ~(1<<index);

        m_fixture->SetFilterData(filter);
    } else {
        LOG_ERROR << "Couldn't find the collision layer id: " << id;
        exit(1);
    }
}

b2Filter sge::cmp::Collider::get_filter_data() {
    return m_fixture->GetFilterData();
}

void sge::cmp::Collider::set_collision_with_all_layers(bool enabled) {
    b2Filter filter(m_fixture->GetFilterData());
    uint16 i = 0;
    filter.maskBits = ~i;
    m_fixture->SetFilterData(filter);
}

void sge::cmp::Collider::set_material(const PhysicsMaterial &physics_material) {
    set_density(physics_material.density);
    set_restitution(physics_material.restitution);
    set_friction(physics_material.friction);
}





