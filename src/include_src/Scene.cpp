#include <Scene.hpp>

#include "GameObjectMemoryLayer.hpp"
#include "ComponentFactory.hpp"
#include "Loggable.hpp"
#include "Box2D/Box2D.h"

using namespace sge;
using namespace sge::core;
using namespace sge::cmp;
using utils::Handle;

Scene::Scene(cd::Scene_ConstructionData *scene_construction_data, GameObjectMemoryLayer *_gameobject_memory_layer,
             core::IComponentMemoryLayer **_component_memory_layer_array, IEnvironment *_env)
        : Loggable ("SCENE <" + scene_construction_data->name + ">")
        , gameobject_memory_layer(_gameobject_memory_layer)
        , env_p(_env)
        , m_camera(scene_construction_data->camera_vertical_zoom)
        {
            LOG_DEBUG(18) << "Initiating construction";
            for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
                component_memory_layer_array[i] = _component_memory_layer_array[i];
            }

            b2Vec2 gravity (scene_construction_data->gravity.x,scene_construction_data->gravity.y);
            m_b2_world = new b2World(gravity);

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
    delete (m_b2_world);
}

Camera *Scene::get_camera() {
    return &m_camera;
}

void Scene::set_gravity(sge::Vec2<float> gravity_vec) {
    m_b2_world->SetGravity(b2Vec2(gravity_vec.x, gravity_vec.y));
}

void Scene::raycast(RayCastHandler* handler) {
    b2Vec2 pointA = b2Vec2(handler->get_point_a().x, handler->get_point_a().y);
    b2Vec2 pointB = b2Vec2(handler->get_point_b().x, handler->get_point_b().y);
    handler->prepare_for_raycast();
    m_b2_world->RayCast(handler, pointA, pointB);
}

b2World *Scene::get_b2World() {
    return  m_b2_world;
}

IEnvironment *Scene::env() {
    return env_p;
}

void Scene::doom_scene() {
    env()->doom_scenes(1);
}

bool Scene::is_doomed() {return env()->is_top_scene_doomed(); }


