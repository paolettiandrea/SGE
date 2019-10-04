//
// Created by andrea on 5/2/19.
//

#ifndef SGE_SCENECONSTRUCTIONDATA_HPP
#define SGE_SCENECONSTRUCTIONDATA_HPP

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
        /*!
         * \brief Constructor
         * \param _name The name of the Scene
         * \param _initial_logic A pointer to the initial Logic that will be injected in the Scene on creation
         */
        SceneConstructionData(const std::string& _name, Logic* _initial_logic)
                : name(_name)
                , initial_logic(_initial_logic)
                , gravity(0,9.8) {  }

        /*!
         * \brief The name of the Scene
         */
        const std::string name;
        /*!
         * \brief A pointer to the Logic that will be injected in the initial gameobject of the newly created scene
         */
        Logic* initial_logic;
        /**
         * \brief Defines the zoom of the camera by the game world units of vertical space that the Camera should show in a given moment
         */
        float camera_vertical_zoom = 10;

        sge::Vec2<float> gravity;
    };
    }

}





/*!
 * \brief Object meant to contain all the data necessary to build a Scene object.
 */

#endif //SGE_SCENECONSTRUCTIONDATA_HPP
