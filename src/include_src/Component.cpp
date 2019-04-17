//
// Created by andrea on 4/15/19.
//

#include <SGE/components/Component.hpp>

#include "SGE/components/Component.hpp"

Component::Component(Handle<GameObject> gameobject)
    : my_gameobject(gameobject) {

}

const Handle<GameObject> &Component::gameobject() const {
    return my_gameobject;
}
