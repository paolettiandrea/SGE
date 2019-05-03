#ifndef FACTORY_EXPERIMENTS_SCENE_HPP
#define FACTORY_EXPERIMENTS_SCENE_HPP

#include <SGE/engine/IEnvironment.hpp>
#include "SGE/GameObject.hpp"
#include "SGE/Macros.hpp"
#include "SGE/utils/handles/Handle.hpp"
#include "SGE/SceneConstructionData.hpp"

namespace sge {

    namespace core {
        class GameObjectMemoryLayer;
        class IComponentMemoryLayer;
    }


/*!
 * \brief .....
 */
    class Scene : public utils::log::Loggable {
    public:

        explicit Scene(SceneConstructionData* scene_construction_data);

        virtual ~Scene();

        /*!
         * \brief Spawns a new GameObject in this Scene
         * \return an Handle referencing to the spawn GameObject
         */
        utils::Handle<GameObject> spawn_gameobject(const std::string& name);
        /*!
         * \brief Gets an array of pointers to every ComponentMemoryLayer of this scene, one for each type at the index
         * expected from the id_to_index correspondence
         */
        core::IComponentMemoryLayer** get_component_memorylayer_array();

        IEnvironment* env() {
            return env_p;
        }


    private:
        /*!
         * \brief The GameObject/Component calls to the creation methods of the factory should pass through the scene, so that it can enforce the call only on its index
         */
        core::GameObjectMemoryLayer* gameobject_memory_layer;
        /*!
         * \brief Array of pointers to each IComponentMemoryLayer (unspecified interface of ComponentMemoryLayer) of this Scene, one for each type
         * at the index expected from the id_to_index correspondance
         */
        core::IComponentMemoryLayer* component_memory_layer_array[TOTAL_POSSIBLE_COMPONENTS];
        /*!
         * \brief A pointer to the IEnvironment interface of the Engine
         */
        IEnvironment* env_p;
    };
}









#endif //FACTORY_EXPERIMENTS_SCENE_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/




/*!
\file
\brief Header file.
*/