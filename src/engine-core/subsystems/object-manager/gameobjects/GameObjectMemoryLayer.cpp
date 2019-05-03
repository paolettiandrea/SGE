#include "GameObjectMemoryLayer.hpp"

// TEMP
#include <iostream>

using sge::core::GameObjectMemoryLayer;
using sge::GameObject;
using utils::Handle;

GameObjectMemoryLayer::GameObjectMemoryLayer(unsigned int initial_reserved_spaces)
    : Loggable("GAME OBJECT MEMORY LAYER"){
    gameobjects_vector.reserve(initial_reserved_spaces);
}

Handle<GameObject> GameObjectMemoryLayer::create_new_gameobject(const std::string& name, Scene* scene) {
    if (gameobjects_vector.size()==gameobjects_vector.capacity())
        custom_realloc();

    gameobjects_vector.emplace_back(scene, name);               // GameObject CONSTRUCTION at the back of the vector
    return gameobjects_vector.back().get_handle();
}

void GameObjectMemoryLayer::custom_realloc() {
    LOG_DEBUG(18) << "Reached maximum capacity of [" << gameobjects_vector.capacity() << "], reallocating vector";
    gameobjects_vector.reserve(gameobjects_vector.capacity()*2);

    // Updates the handle entries of every GameObject in the reallocated vector
    for (auto &gameobj : gameobjects_vector) {
        gameobj.get_handle().update_origin_pointer(&gameobj);
    }
    //Handle<GameObject>::print_entries_array_info();
}

void GameObjectMemoryLayer::remove_gameobject(Handle<GameObject> target_handle) {
    // If we're removing the last element there's no need of memory swapping shenanigans
    // else the last element is swapped in the gap created by the removal and the corresponfing handle origin pointer is updated
    auto target_pointer = target_handle.get_pointer();
    if (target_pointer != &gameobjects_vector.back()) {
        GameObject* last_element_pointer = &gameobjects_vector.back();
        last_element_pointer->get_handle().update_origin_pointer(target_pointer);
        target_pointer->swap(gameobjects_vector.back());
    }
    target_handle.make_origin_expired();
    gameobjects_vector.pop_back();
}

std::vector<GameObject>* GameObjectMemoryLayer::get_gameobjects_vector() {
    return &gameobjects_vector;
}

void GameObjectMemoryLayer::doom_pass() {
    LOG_DEBUG(25) << "Doom pass";
    int target_index = 0;
    for (int i = 0; i < gameobjects_vector.size(); ++i) {
        GameObject* target_gameobj_p = &gameobjects_vector[target_index];
        if (target_gameobj_p->is_doomed()) {
            Handle<GameObject> go = target_gameobj_p->get_handle();
            remove_gameobject(go);
        } else {
            target_index++;
        }
    }


}




