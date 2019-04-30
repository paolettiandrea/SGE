#include "ObjectManager.hpp"


Scene* ObjectManager::push_new_scene(Logic* initial_logic) {
    LOG_DEBUG(15) << "Pushing a new scene";
    gameobj_layers_stack.emplace();

    IComponentMemoryLayer* componentarray_out[TOTAL_POSSIBLE_COMPONENTS];
    component_factory.push_new_component_memory_layer(componentarray_out);

    scene_stack.emplace(scene_stack.size(), &gameobj_layers_stack.top(), componentarray_out, initial_logic);
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
    LOG_DEBUG(17) << "Starting doom pass";
    auto component_memory_array = scene_stack.top().get_component_memorylayer_array();
    for (int i = 0; i < TOTAL_POSSIBLE_COMPONENTS; ++i) {
        component_memory_array[i]->doom_pass();
    }
    gameobj_layers_stack.top().doom_pass();


}
