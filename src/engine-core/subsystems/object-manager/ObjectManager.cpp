#include "ObjectManager.hpp"
#include "Logic.hpp"

using sge::core::ObjectManager;
using sge::Scene;
using sge::cd::SceneConstructionData;

Scene* ObjectManager::push_new_scene(SceneConstructionData *scene_construction_data) {
    gameobj_layers_stack.emplace();
    LOG_DEBUG(30) << "Pushing a new GameObjectMemoryLayer on top of the stack";
    auto gameobj_mem_layer = &gameobj_layers_stack.top();

    IComponentMemoryLayer* comp_mem_layer_array[TOTAL_POSSIBLE_COMPONENTS];
    component_factory.push_new_component_memory_layer(comp_mem_layer_array);

    scene_stack.emplace(scene_construction_data, gameobj_mem_layer, comp_mem_layer_array, env);
    return &scene_stack.top();

}

Scene *ObjectManager::get_top_scene() {
    return &scene_stack.top();
}

void ObjectManager::pop_top_scene() {
    component_factory.pop_top_component_memory_layer();
    gameobj_layers_stack.pop();
    scene_stack.pop();
}

unsigned int ObjectManager::get_scene_stack_size() {
    return scene_stack.size();
}

void ObjectManager::doom_pass() {
    // TODO optimization: right now the whole top scene array is scrolled, could save the index of doomed objects on doom and work with that
    LOG_DEBUG(15) << "Starting doom pass";
    for (auto & gameobj : (*gameobj_layers_stack.top().get_gameobjects_vector())) {
        if (gameobj.is_doomed()) {
            // Every component attached to the doomed gameobject is doomed
            for (int id_index = 0; id_index < TOTAL_POSSIBLE_COMPONENTS; ++id_index) {
                int unspecified_index = gameobj.m_components_mapped_array[id_index];
                if (unspecified_index != -1) {
                    scene_stack.top().get_component_memorylayer_array()[id_index]
                    ->doom_unspecified_component(unspecified_index);
                }
            }
            // on_destruction is called on every Logic object attached to the doomed gameobject right before
            // the actual removal pass is started
            gameobj.logichub()->on_destruction();
        }
    }

    // Doom pass for the Components
    auto component_memory_array = scene_stack.top().get_component_memorylayer_array();
    for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
        component_memory_array[i]->doom_pass();
    }
    gameobj_layers_stack.top().doom_pass();

    LOG_DEBUG(15) << "Doom pass terminated";

}

void ObjectManager::scene_pass() {
    LOG_DEBUG(15) << "Starting scene pass";
    if (pop_top_scene_flag) {
        LOG_DEBUG(15) << "Popping the top scene (since pop_top_scene_flag == true)";
        pop_top_scene();
        pop_top_scene_flag = false;
    }
    if (new_scene_construction_data != nullptr) {
        LOG_DEBUG(15) << "Pushing a new scene (since new_scene_construction_data != nullptr)";
        SceneConstructionData* temp_pointer = new_scene_construction_data;
        new_scene_construction_data = nullptr;          // It's nulled before the push so that there's no conflict
        push_new_scene(temp_pointer);                   // if during scene creation some logic wants to book a push
        delete( temp_pointer );
    }
    LOG_DEBUG(15) << "Ending scene pass";
}

bool ObjectManager::book_scene_push(const std::string &name, Logic *initial_logic) {
    bool book_successfull = false;
    if (new_scene_construction_data == nullptr) {
        new_scene_construction_data = new SceneConstructionData(name, initial_logic);
        book_successfull = true;
    }
    return  book_successfull;
}

void ObjectManager::doom_top_scene() {
    pop_top_scene_flag = true;
}

ObjectManager::~ObjectManager() {
    LOG_DEBUG(30) << "Destructor";
    if (new_scene_construction_data != nullptr) {                           // There was a scene booked for pushing
        LOG_DEBUG(30) << "Since there was a scene push booked deleting the Logic given as initial logic gìfor the booked Scene";
        delete((new_scene_construction_data->initial_logic));               // so some stuff needs to be deleted
        delete(new_scene_construction_data);
    }
}
