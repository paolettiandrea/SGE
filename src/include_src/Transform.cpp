#include "Transform.hpp"
#include "GameObject.hpp"
#include <math.h>
#include <vector>

using sge::cmp::Transform;
using utils::Handle;

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

sge::Vec2<double> sge::cmp::Transform::get_local_position() {
    return m_local_position_vector;
}

void sge::cmp::Transform::set_local_position(double x, double y) {
    m_local_position_vector.x = x;
    m_local_position_vector.y = y;
    make_dirty();
}

void sge::cmp::Transform::set_local_scale(double scale) {
    m_local_scale_matrix[0][0] = scale;
    m_local_scale_matrix[1][1] = scale;
    make_dirty();
}


void sge::cmp::Transform::set_local_rotation(double rads) {
    float sin = std::sin(rads);
    float cos = std::cos(rads);
    m_local_rotation_matrix[0][0] = cos;
    m_local_rotation_matrix[1][1] = cos;
    m_local_rotation_matrix[0][1] = -sin;
    m_local_rotation_matrix[1][0] = sin;
    make_dirty();
}

sge::Vec2<double> sge::cmp::Transform::local_to_world_point(sge::Vec2<double> point) {
    if (is_dirty) update_world_data();
    Matrix2D<double> point_matrix(2,1);
    point_matrix[0][0] = point.x;
    point_matrix[1][0] = point.y;
    auto yo = m_world_rotation_matrix*(m_world_scale_matrix*point_matrix);
    return sge::Vec2<double>(yo[0][0]+m_world_position_vector.x, yo[1][0]+m_world_position_vector.y);
}

void sge::cmp::Transform::make_dirty() {
    if (!is_dirty) {
        is_dirty = true;
        transform_diry_event();
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

        Matrix2D<double> temp(2,2);
        temp[0][0] = m_local_position_vector.x;
        temp[1][0] = m_local_position_vector.y;

        auto yo =temp * m_parent->m_world_scale_matrix * m_parent->m_world_rotation_matrix ;
        m_world_position_vector.x = yo[0][0];
        m_world_position_vector.y = yo[1][0];
        m_world_position_vector = m_world_position_vector + m_parent->m_world_position_vector;

    } else {
        m_world_position_vector = m_local_position_vector;
        m_world_scale_matrix = m_local_scale_matrix;
        m_world_rotation_matrix = m_local_rotation_matrix;
    }
}

sge::Vec2<double> sge::cmp::Transform::get_world_position() {
    if (is_dirty) update_world_data();
    return m_world_position_vector;
}

sge::Vec2<double> sge::cmp::Transform::get_local_scale() {
    return Vec2(m_local_scale_matrix[0][0], m_local_scale_matrix[1][1]);
}

sge::Vec2<double> sge::cmp::Transform::get_world_scale() {
    if (is_dirty) update_world_data();
    return Vec2(m_world_scale_matrix[0][0], m_world_scale_matrix[1][1]);
}

double sge::cmp::Transform::get_local_rotation() {
    return acos(m_local_rotation_matrix[0][0]);
}

double sge::cmp::Transform::get_local_rotation_euler() {
    return get_local_rotation() * 180 / M_PI;
}

double sge::cmp::Transform::get_world_rotation() {
    if (is_dirty) update_world_data();
    return acos(m_world_rotation_matrix[0][0]);
}

double sge::cmp::Transform::get_world_rotation_euler() {
    return  get_world_rotation() * 180 / M_PI;
}















