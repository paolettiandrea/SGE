//
// Created by andrea on 4/17/19.
//

#include "Transform.hpp"

using sge::Transform;
using utils::Handle;

Transform::Transform(const Handle<GameObject> &gameobject)
    : Component(gameobject, "Transform") {}

