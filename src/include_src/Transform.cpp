//
// Created by andrea on 4/17/19.
//

#include "Transform.hpp"

using sge::cmp::Transform;
using utils::Handle;

Transform::Transform(const Handle<GameObject> &gameobject)
    : Component(gameobject, "Transform")
    , local_position(0.f,0.f)
    {}

void Transform::set_parent(Handle<Transform> new_parent) {
    if (!this->parent.is_null()) {

        }
        this->parent.make_null();
    }


