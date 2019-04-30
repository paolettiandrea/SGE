#include <Scene.hpp>

#include "GameObjectMemoryLayer.hpp"
#include "ComponentFactory.hpp"
#include "Loggable.hpp"

Scene::Scene(unsigned int _index, GameObjectMemoryLayer* _gameobj_memory_layer, IComponentMemoryLayer* _componentarrays_array[], Logic* initial_logic)
        : Loggable ("SCENE [" + std::to_string(_index) + "]")
        , index(_index)
        , gameobject_memory_layer(_gameobj_memory_layer)
        {
            LOG_DEBUG(18) << "Initiating construction";
            for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
                component_memory_layer_array[i] = _componentarrays_array[i];
            }

            auto initial_gameobj = spawn_gameobject("Initial GameObject");
            initial_gameobj->get_component<LogicHub>("LogicHub")->attach_logic(initial_logic);
        }

Handle<GameObject> Scene::spawn_gameobject(const std::string& name) {
    LOG_DEBUG(12) << "Spawning a new GameObject named [" + name + "]";
    return gameobject_memory_layer->create_new_gameobject(name, this);
}

void Scene::destroy_gameobject(Handle<GameObject> target_handle) {
    LOG_DEBUG(12) << "Removing the GameObject named [" + target_handle->get_log_id() + "]";
    gameobject_memory_layer->remove_gameobject(target_handle);
}

IComponentMemoryLayer *const *Scene::get_component_memorylayer_array() const {
    return component_memory_layer_array;
}

Scene::~Scene() {
    LOG_DEBUG(15) << "Destruction";
}


