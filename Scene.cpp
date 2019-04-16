//
// Created by andrea on 4/15/19.
//

#include "Scene.hpp"

Scene::Scene(unsigned int _index)
        : index(_index)
        , gameobject_memory_layer(this) {

}

Handle<GameObject> Scene::spawn_gameobject(const std::string& name) {
    return gameobject_memory_layer.create_new_gameobject(name);
}

void Scene::destroy_gameobject(Handle<GameObject> target_handle) {
    gameobject_memory_layer.remove_gameobject(target_handle);
}
