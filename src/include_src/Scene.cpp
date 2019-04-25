
#include <SGE/Scene.hpp>

#include "Scene.hpp"
#include "gameobjects/GameObjectMemoryLayer.hpp"
#include "ComponentFactory.hpp"

Scene::Scene(unsigned int _index, GameObjectMemoryLayer* _gameobj_memory_layer, IComponentMemoryLayer* _componentarrays_array[])
        : index(_index)
        , gameobject_memory_layer(_gameobj_memory_layer)
        {
            for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
                component_memory_layer_array[i] = _componentarrays_array[i];
            }
        }

Handle<GameObject> Scene::spawn_gameobject(const std::string& name) {
    return gameobject_memory_layer->create_new_gameobject(name, this);
}

void Scene::destroy_gameobject(Handle<GameObject> target_handle) {
    gameobject_memory_layer->remove_gameobject(target_handle);
}

IComponentMemoryLayer *const *Scene::get_component_memorylayer_array() const {
    return component_memory_layer_array;
}


