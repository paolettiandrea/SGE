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

    namespace cd {
    /*!
     * \brief Object that holds all the user dependent information necessary in order to build a Scene
     */
    struct SceneConstructionData {
        SceneConstructionData(const std::string& _name, Logic* _initial_logic)
                : name(_name)
                , initial_logic(_initial_logic){  }

        const std::string name;
        Logic* initial_logic;
    };
    }

}





/*!
 * \brief Object meant to contain all the data necessary to build a Scene object.
 */

#endif //FACTORY_EXPERIMENTS_SCENECONSTRUCTIONDATA_HPP
