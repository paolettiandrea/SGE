#include "Transform.hpp"
#include "GameObject.hpp"
#include "Scene.hpp"
#include <math.h>
#include <vector>

using sge::cmp::Transform;
using utils::Handle;

bool sge::cmp::Transform::visual_debug_general_switch = false;
bool sge::cmp::Transform::visual_debug_show_names = false;


Transform::Transform(const Handle<GameObject> &gameobject)
    : Component(gameobject, "Transform")
    , m_local_position_vector(0.f,0.f)
    , m_local_rotation_matrix(2,2)
    , m_local_scale_matrix(2,2)
    , m_world_position_vector(0.f,0.f)
    , m_world_rotation_matrix(2,2)
    , m_world_scale_matrix(2,2)
    {
    m_local_rotation_matrix.make_identity();
    m_local_scale_matrix.make_identity();
    }

void Transform::set_parent(Handle<Transform> new_parent) {
    if (!this->m_parent.is_null() && this->m_parent!=new_parent) {
        this->m_parent->remove_child(this->get_handle());
    }
    if (!new_parent.is_null()) {
        // Check for circular hierarchy
        Handle<Transform> target_parent = new_parent;
        while (!target_parent.is_null()) {
            if (target_parent == this->get_handle()) {
                LOG_ERROR << "Detected circular hierarchy while trying to set " << new_parent->gameobject()->get_log_id()
                          << " as m_parent. This object's local hierarchy before this operation looks as follows:\n"
                          << gameobject()->get_string_local_hierarchy();
                exit(1);
            }
            target_parent = target_parent->get_parent();
        }

        // Add this as child to the new parent
        new_parent->add_child(this->get_handle());
    }

    this->m_parent = new_parent;
    this->make_dirty();

    parent_changed_event();
}

utils::Handle<Transform> sge::cmp::Transform::get_parent() {
    return m_parent;
}

void sge::cmp::Transform::add_child(utils::Handle<Transform> new_child) {
    for (auto child : m_children) {
        if (child==new_child) {
            LOG_WARNING << "Tried to add a child that was already present in the child list";
            return;
        }
    }
    m_children.push_back(new_child);
}

void sge::cmp::Transform::remove_child(utils::Handle<Transform> target_child) {
    m_children.remove(target_child);
}

std::list<utils::Handle<Transform>> sge::cmp::Transform::get_children_list() {
    return m_children;
}

sge::Vec2<float> sge::cmp::Transform::get_local_position() {
    return m_local_position_vector;
}

void sge::cmp::Transform::set_local_position(float x, float y) {
    m_local_position_vector.x = x;
    m_local_position_vector.y = y;
    make_dirty();
}

void sge::cmp::Transform::set_local_scale(float scale) {
    if (scale==0.f) {
        LOG_ERROR << "Scale cannot be 0";
        exit(1);
    }
    if (m_local_scale_matrix[0][0]!=scale || m_local_scale_matrix[1][1]!=scale) {
        m_local_scale_matrix[0][0] = scale;
        m_local_scale_matrix[1][1] = scale;
        make_dirty();
    }
}


void sge::cmp::Transform::set_local_rotation(float rads) {
    auto diff = rads - get_local_rotation();
    if (diff != 0) {
        float sin = std::sin(rads);
        float cos = std::cos(rads);
        m_local_rotation_matrix[0][0] = cos;
        m_local_rotation_matrix[1][1] = cos;
        m_local_rotation_matrix[0][1] = -sin;
        m_local_rotation_matrix[1][0] = sin;
        make_dirty();
    }
}

sge::Vec2<float> sge::cmp::Transform::local_to_world_point(sge::Vec2<float> point) {
    if (is_dirty) update_world_data();
    Matrix2D<float> point_matrix(2,1);
    point_matrix[0][0] = point.x;
    point_matrix[1][0] = point.y;
    auto yo = m_world_rotation_matrix*m_world_scale_matrix*point_matrix;
    return sge::Vec2<float>(yo[0][0]+m_world_position_vector.x, yo[1][0]+m_world_position_vector.y);
}


sge::Vec2<float> sge::cmp::Transform::world_to_local_point(sge::Vec2<float> world_pos) {
    if (is_dirty) update_world_data();
    Matrix2D<float> point_matrix(2,1);
    point_matrix[0][0] = world_pos.x;       // BOH...
    point_matrix[1][0] = world_pos.y;
    Matrix2D<float> inverse_scale = m_world_scale_matrix;
    inverse_scale[0][0] = 1 / inverse_scale[0][0];
    inverse_scale[1][1] = 1 / inverse_scale[1][1];
    m_world_scale_matrix.print_matrix("world scale");
    auto yo = point_matrix*inverse_scale*m_world_rotation_matrix.transpose();
    return sge::Vec2<float>(yo[0][0], yo[1][0]);
}

void sge::cmp::Transform::make_dirty() {
    transform_changed_event();
    if (!is_dirty) {
        is_dirty = true;
        for (auto child : m_children) {     // OPTIMIZE: maybe we can stop when we encounter already dirty transforms
            child->make_dirty();
        }
    }

}

void sge::cmp::Transform::update_world_data() {
    // Traversing the hierarchy upstream until root or not-dirty Transform is found, creating a vector of pointers to the Transforms that need to be updated, in the reverse order they need to be updated
    std::vector<Handle<Transform>> dirty_parents_vec;
    Handle<Transform> target = this->get_handle();
    while (!target.is_null() && target->is_dirty) {
        dirty_parents_vec.push_back(target);
        target = target->get_parent();
    }
    for (int i = dirty_parents_vec.size()-1; i >= 0; --i) {
            dirty_parents_vec[i]->compose_with_parent();
            dirty_parents_vec[i]->is_dirty = false;
    }
}

void sge::cmp::Transform::compose_with_parent() {
    if (!m_parent.is_null()) {
        m_world_scale_matrix = m_parent->m_world_scale_matrix*m_local_scale_matrix;
        m_world_rotation_matrix = m_parent->m_world_rotation_matrix*m_local_rotation_matrix;

        Matrix2D<float> temp(2,2);
        temp[0][0] = m_local_position_vector.x;
        temp[1][0] = m_local_position_vector.y;

        auto res = m_parent->m_world_rotation_matrix *  m_parent->m_world_scale_matrix * temp;
        m_world_position_vector.x = res[0][0];
        m_world_position_vector.y = res[1][0];
        m_world_position_vector = m_world_position_vector + m_parent->m_world_position_vector;

    } else {
        m_world_position_vector = m_local_position_vector;
        m_world_scale_matrix = m_local_scale_matrix;
        m_world_rotation_matrix = m_local_rotation_matrix;
    }
}

sge::Vec2<float> sge::cmp::Transform::get_world_position() {
    if (is_dirty) update_world_data();
    return m_world_position_vector;
}

sge::Vec2<float> sge::cmp::Transform::get_local_scale() {
    return Vec2(m_local_scale_matrix[0][0], m_local_scale_matrix[1][1]);
}

sge::Vec2<float> sge::cmp::Transform::get_world_scale() {
    if (is_dirty) update_world_data();
    return Vec2(m_world_scale_matrix[0][0], m_world_scale_matrix[1][1]);
}

float sge::cmp::Transform::get_local_rotation() {
    if (asin(m_local_rotation_matrix[0][1])<0)
        return acos(m_local_rotation_matrix[0][0]);
    else return acos(-m_local_rotation_matrix[0][0]) + M_PI;

}

float sge::cmp::Transform::get_local_rotation_euler() {
    return get_local_rotation() * 180 / M_PI;
}

float sge::cmp::Transform::get_world_rotation() {
    if (is_dirty) update_world_data();
    if (asin(m_world_rotation_matrix[0][1])<0)
        return acos(m_world_rotation_matrix[0][0]);
    else return acos(-m_world_rotation_matrix[0][0]) + M_PI;
}

float sge::cmp::Transform::get_world_rotation_euler() {
    if (is_dirty) update_world_data();
    return  get_world_rotation() * 180 / M_PI;
}


void sge::cmp::Transform::visual_debug_pass() {
    auto env_h = gameobject()->get_scene()->env();
    env_h->debug_draw_direction(m_world_position_vector, local_to_world_point(sge::Vec2<float>(0,3)),0.f,sf::Color(199,19,29));
    env_h->debug_draw_direction(m_world_position_vector, local_to_world_point(sge::Vec2<float>(3,0)), 0.f, sf::Color(199,193,23));
    if (visual_debug_show_names)
        env_h->debug_draw_point(m_world_position_vector,0.f,gameobject()->get_log_id(),0,sf::Color(200,200,200));
}

















