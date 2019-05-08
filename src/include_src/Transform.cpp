#include "Transform.hpp"
#include "GameObject.hpp"

using sge::cmp::Transform;
using utils::Handle;

Transform::Transform(const Handle<GameObject> &gameobject)
    : Component(gameobject, "Transform")
    , m_local_position(0.f,0.f)
    , m_local_rotation_angle(0.f)
    , m_local_scale (1.f)
    {}

void Transform::set_parent(Handle<Transform> new_parent) {
    if (!this->parent.is_null() && this->parent!=new_parent) {
        this->parent->remove_child(this->get_handle());
    }
    // Check for circular hierarchy
    Handle<Transform> target_parent = new_parent;
    while (!target_parent.is_null()) {
        if (target_parent == this->get_handle()) {
            LOG_ERROR << "Detected circular hierarchy while trying to set " << new_parent->gameobject()->get_log_id()
                      << " as parent. This object's local hierarchy before this operation looks as follows:\n"
                      << gameobject()->get_string_local_hierarchy();
            exit(1);
        }
        target_parent = target_parent->get_parent();
    }

    new_parent->add_child(this->get_handle());
    this->parent = new_parent;
}

utils::Handle<Transform> sge::cmp::Transform::get_parent() {
    return parent;
}

void sge::cmp::Transform::add_child(utils::Handle<Transform> new_child) {
    children.push_back(new_child);
}

void sge::cmp::Transform::remove_child(utils::Handle<Transform> target_child) {
    children.remove(target_child);
}

std::list<utils::Handle<Transform>> sge::cmp::Transform::get_children_list() {
    return children;
}







