#include "Factory.hpp"


Scene* Factory::push_new_scene() {
    LOG_DEBUG(15) << "Pushing a new scene";
    gameobj_layers_stack.emplace();

    IComponentMemoryLayer* componentarray_out[TOTAL_POSSIBLE_COMPONENTS];
    component_factory.push_new_component_memory_layer(componentarray_out);

    scene_stack.emplace(scene_stack.size(), &gameobj_layers_stack.top(), componentarray_out);
    return &scene_stack.top();

}

Scene *Factory::get_top_scene() {
    return &scene_stack.top();
}

void Factory::pop_top_scene() {
    LOG_DEBUG(15) << "Popping the top Scene";
    scene_stack.pop();
}