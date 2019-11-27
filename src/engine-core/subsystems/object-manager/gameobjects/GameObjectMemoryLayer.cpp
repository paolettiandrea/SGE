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

bool GameObjectMemoryLayer::remove_gameobject(Handle<GameObject> target_handle) {
    // If we're removing the last element there's no need of memory swapping shenanigans
    // else the last element is swapped in the gap created by the removal and the corresponfing handle origin pointer is updated
    bool swap_happened = false;

    auto target_pointer = target_handle.get_pointer();
    if (target_pointer != &gameobjects_vector.back()) {
        gameobjects_vector.back().get_handle().update_origin_pointer(target_handle.get_pointer());
        int target_internal_index = target_handle.get_pointer() - &gameobjects_vector[0];
        std::swap(gameobjects_vector[target_internal_index], gameobjects_vector[gameobjects_vector.size() - 1]);
        swap_happened = true;
    }
    target_handle.make_origin_expired();
    gameobjects_vector.pop_back();
    return swap_happened;
}

std::vector<GameObject>* GameObjectMemoryLayer::get_gameobjects_vector() {
    return &gameobjects_vector;
}

/**
 * /brief Remove all the doomed GameObjects from this GameObjectMemoryLayer
 */
void GameObjectMemoryLayer:: doom_pass() {
    LOG_DEBUG(25) << "Doom pass";
    for (int i = 0; i < gameobjects_vector.size(); ++i) {
        GameObject* target_gameobj_p = &gameobjects_vector[i];
        if (target_gameobj_p->is_doomed()) {
            Handle<GameObject> go = target_gameobj_p->get_handle();
            if (remove_gameobject(go)) i--;
            LOG_DEBUG(30) << "Removed " << target_gameobj_p;
        }
    }


}




