#include "Transform.hpp"
#include "GameObject.hpp"
#include <math.h>

using sge::cmp::Transform;
using utils::Handle;

Transform::Transform(const Handle<GameObject> &gameobject)
    : Component(gameobject, "Transform")
    , m_local_position(0.f,0.f)
    , m_local_rotation_angle(0.f)
    , m_local_scale (1.f)
    {}

void Transform::set_parent(Handle<Transform> new_parent) {
    if (!this->m_parent.is_null() && this->m_parent!=new_parent) {
        this->m_parent->remove_child(this->get_handle());
    }
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

    new_parent->add_child(this->get_handle());
    this->m_parent = new_parent;
}

utils::Handle<Transform> sge::cmp::Transform::get_parent() {
    return m_parent;
}

void sge::cmp::Transform::add_child(utils::Handle<Transform> new_child) {
    m_children.push_back(new_child);
}

void sge::cmp::Transform::remove_child(utils::Handle<Transform> target_child) {
    m_children.remove(target_child);
}

std::list<utils::Handle<Transform>> sge::cmp::Transform::get_children_list() {
    return m_children;
}


sge::Vec2<double> sge::cmp::Transform::get_local_position() {
    return m_local_position;
}

void sge::cmp::Transform::set_local_position(double x, double y) {
    m_local_position.x = x;
    m_local_position.y = y;
}

void sge::cmp::Transform::set_local_scale(double scale) {
    m_local_scale = scale;
}

double sge::cmp::Transform::get_local_scale() {
    return m_local_scale;
}

void sge::cmp::Transform::set_local_rotation(double rotation) {
    m_local_rotation_angle = rotation;
}

double sge::cmp::Transform::get_local_rotation() {
    return m_local_rotation_angle;
}

sge::Vec2<double> sge::cmp::Transform::get_world_position() {
    if (m_parent.is_null()) return m_local_position;
    else {
        LOG_ERROR << "Not implemented";         // https://www.gamedev.net/articles/programming/math-and-physics/making-a-game-engine-transformations-r3566/
        exit(1);
    }
}

double sge::cmp::Transform::get_world_scale() {
    if (m_parent.is_null()) return m_local_scale;
    else {
        LOG_ERROR << "Not implemented";
        exit(1);
    }
}

double sge::cmp::Transform::get_world_rotation() {
    if (m_parent.is_null()) return m_local_rotation_angle;
    else {
        LOG_ERROR << "Not implemented";
        exit(1);
    }
}













