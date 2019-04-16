//
// Created by andrea on 4/15/19.
//

#include "GameObject.hpp"

#include <iostream>

GameObject::GameObject(Scene* _scene, const std::string& _name)
    : scene(_scene)
    , name(_name)
    , handle(this){
    std::cout << "Construction of GameObject " << name << std::endl;
}

GameObject::~GameObject() {
    std::cout << "Destruction of GameObject " << name << std::endl;
    handle.make_origin_expired();
}

Handle<GameObject> &GameObject::get_handle() {
    return handle;
}







