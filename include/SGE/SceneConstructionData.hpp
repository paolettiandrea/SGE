//
// Created by andrea on 5/2/19.
//

#ifndef FACTORY_EXPERIMENTS_SCENECONSTRUCTIONDATA_HPP
#define FACTORY_EXPERIMENTS_SCENECONSTRUCTIONDATA_HPP

#include "Macros.hpp"
#include <string>

namespace sge {

    class IEnvironment;
    class Logic;

    namespace core {

        class GameObjectMemoryLayer;
        class IComponentMemoryLayer;
    }

    struct SceneConstructionData {
        SceneConstructionData(const std::string& _name) : name(_name) {  }

        const std::string name;
        core::GameObjectMemoryLayer* gameobj_memory_layer;
        core::IComponentMemoryLayer* componentarrays_array[TOTAL_POSSIBLE_COMPONENTS];
        IEnvironment* env;
        Logic* initial_logic;
    };
}





/*!
 * \brief Object meant to contain all the data necessary to build a Scene object.
 */

#endif //FACTORY_EXPERIMENTS_SCENECONSTRUCTIONDATA_HPP
