#include "ObjectManager.hpp"


Scene* ObjectManager::push_new_scene(Logic* initial_logic) {
    LOG_DEBUG(11) << "Pushing a new m_scene";
    gameobj_layers_stack.emplace();

    IComponentMemoryLayer* componentarray_out[TOTAL_POSSIBLE_COMPONENTS];
    component_factory.push_new_component_memory_layer(componentarray_out);

    scene_stack.emplace(scene_stack.size(), &gameobj_layers_stack.top(), componentarray_out, env, initial_logic);
    return &scene_stack.top();

}

Scene *ObjectManager::get_top_scene() {
    return &scene_stack.top();
}

void ObjectManager::pop_top_scene() {
    LOG_DEBUG(15) << "Popping the top Scene";
    component_factory.pop_top_component_memory_layer();
    gameobj_layers_stack.pop();
    scene_stack.pop();
}

unsigned int ObjectManager::get_scene_stack_size() {
    return scene_stack.size();
}

void ObjectManager::doom_pass() {
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

    auto component_memory_array = scene_stack.top().get_component_memorylayer_array();
    for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
        component_memory_array[i]->doom_pass();
    }
    gameobj_layers_stack.top().doom_pass();


}
