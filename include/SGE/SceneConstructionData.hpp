//
// Created by andrea on 5/2/19.
//

#ifndef FACTORY_EXPERIMENTS_SCENECONSTRUCTIONDATA_HPP
#define FACTORY_EXPERIMENTS_SCENECONSTRUCTIONDATA_HPP

#include "Macros.hpp"
#include <string>
class GameObjectMemoryLayer;
class IComponentMemoryLayer;
class IEnvironment;
class Logic;

/*!
 * \brief Object meant to contain all the data necessary to build a Scene object.
 */
struct SceneConstructionData {
    SceneConstructionData(const std::string& _name) : name(_name) {  }

    const std::string name;
    GameObjectMemoryLayer* gameobj_memory_layer;
    IComponentMemoryLayer* componentarrays_array[TOTAL_POSSIBLE_COMPONENTS];
    IEnvironment* env;
    Logic* initial_logic;
};
#endif //FACTORY_EXPERIMENTS_SCENECONSTRUCTIONDATA_HPP
