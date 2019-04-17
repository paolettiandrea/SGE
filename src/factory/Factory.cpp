#include "Factory.hpp"


unsigned int Factory::build_scene() {
    gameobj_layers_stack.emplace();

    scene_stack.emplace(scene_stack.size(), &gameobj_layers_stack.top());
    return (unsigned int)scene_stack.size()-1;
}

Scene *Factory::get_top_scene() {
    return &scene_stack.top();
}


