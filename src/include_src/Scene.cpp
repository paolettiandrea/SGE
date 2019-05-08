#include <Scene.hpp>

#include "GameObjectMemoryLayer.hpp"
#include "ComponentFactory.hpp"
#include "Loggable.hpp"

using namespace sge;
using namespace sge::core;
using namespace sge::cmp;
using utils::Handle;

Scene::Scene(cd::SceneConstructionData *scene_construction_data, GameObjectMemoryLayer *_gameobject_memory_layer,
             core::IComponentMemoryLayer **_component_memory_layer_array, IEnvironment *_env)
        : Loggable ("SCENE <" + scene_construction_data->name + ">")
        , gameobject_memory_layer(_gameobject_memory_layer)
        , env_p(_env)
        {
            LOG_DEBUG(18) << "Initiating construction";
            for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
                component_memory_layer_array[i] = _component_memory_layer_array[i];
            }

            auto initial_gameobj = spawn_gameobject("Initial GameObject");
            initial_gameobj->get_component<LogicHub>("LogicHub")->attach_logic(scene_construction_data->initial_logic);
        }

Handle<GameObject> Scene::spawn_gameobject(const std::string& name) {
    LOG_DEBUG(12) << "Spawning a new GameObject named [" + name + "]";
    return gameobject_memory_layer->create_new_gameobject(name, this);
}


IComponentMemoryLayer * *Scene::get_component_memorylayer_array() {
    return component_memory_layer_array;
}

Scene::~Scene() {
    LOG_DEBUG(15) << "Destruction";
}


