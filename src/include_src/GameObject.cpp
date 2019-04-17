//
// Created by andrea on 4/15/19.
//

#include "../../include/SGE/GameObject.hpp"

#include <iostream>

GameObject::GameObject(Scene* _scene, const std::string& _name)
    : scene(_scene)
    , name(_name)
    , handle(this){
    std::cout << "Construction of GameObject " << name << std::endl;
}

GameObject::~GameObject() {
    std::cout << "Destruction of GameObject " << name << std::endl;

}

Handle<GameObject> &GameObject::get_handle() {
    return handle;
}







