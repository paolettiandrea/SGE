#include "Scene.hpp"
#include "gameobjects/GameObjectMemoryLayer.hpp"


Scene::Scene(unsigned int _index, GameObjectMemoryLayer* _gameobj_memory_layer)
        : index(_index)
        , gameobject_memory_layer(_gameobj_memory_layer)
        { }

Handle<GameObject> Scene::spawn_gameobject(const std::string& name) {
    return gameobject_memory_layer->create_new_gameobject(name, this);
}

void Scene::destroy_gameobject(Handle<GameObject> target_handle) {
    gameobject_memory_layer->remove_gameobject(target_handle);
}
