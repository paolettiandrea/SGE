//
// Created by andrea on 4/17/19.
//

#include "Transform.hpp"

Transform::Transform(const Handle<GameObject> &gameobject)
    : Component(gameobject, "Transform") {}
