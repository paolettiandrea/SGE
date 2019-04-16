#include "GameObjectMemoryLayer.hpp"

// TEMP
#include <iostream>

GameObjectMemoryLayer::GameObjectMemoryLayer(Scene* _scene, unsigned int initial_reserved_spaces) : scene(_scene) {
    gameobjects_vector.reserve(initial_reserved_spaces);
}

Handle<GameObject> GameObjectMemoryLayer::create_new_gameobject(const std::string& name) {
    if (gameobjects_vector.size()==gameobjects_vector.capacity())
        custom_realloc();

    gameobjects_vector.emplace_back(scene, name);               // GameObject CONSTRUCTION at the back of the vector
    return gameobjects_vector.back().get_handle();
}

void GameObjectMemoryLayer::custom_realloc() {
    gameobjects_vector.reserve(gameobjects_vector.capacity()*2);

    // Updates the handle entries of every GameObject in the reallocated vector
    for (auto &gameobj : gameobjects_vector) {
        gameobj.get_handle().update_origin_pointer(&gameobj);
    }
    //std::cout << "Reallocation happened" << std::endl;
    //Handle<GameObject>::print_entries_array_info();
}

void GameObjectMemoryLayer::remove_gameobject(Handle<GameObject> target_handle) {
    // If we're removing the last element there's no need of memory swapping shenanigans
    // else the last element is swapped in the gap created by the removal and the corresponfing handle origin pointer is updated
    if (target_handle.get_pointer() != &gameobjects_vector.back()) {
        GameObject* target_pointer = target_handle.get_pointer();
        GameObject* last_element_pointer = &gameobjects_vector.back();
        last_element_pointer->get_handle().update_origin_pointer(target_pointer);
        std::swap(target_pointer, last_element_pointer);
    }
    //target_handle.make_origin_expired();
    gameobjects_vector.pop_back();
}




