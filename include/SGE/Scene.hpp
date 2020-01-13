#ifndef SGE_SCENE_HPP
#define SGE_SCENE_HPP

#include <SGE/engine/IEnvironment.hpp>
#include "SGE/GameObject.hpp"
#include "SGE/Macros.hpp"
#include "SGE/utils/handles/Handle.hpp"
#include "SGE/SceneConstructionData.hpp"
#include <SGE/components/physics/RayCastHandler.hpp>


class b2World;

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
        /*!
         * \brief Constructor ONLY TO BE USED INTERNALLY
         * \param scene_construction_data The class containing all the user defined data needed for constuction
         * \param _gameobject_memory_layer A pointer to the GameObjectMemoryLayer assigned to this Scene
         * \param _component_memory_layer_array A pointer to the ComponentMemoryLayer array assigned to this Scene
         * \param _env A pointer to the IEnvironment, the internal interface of the engine core
         */
        explicit Scene(cd::SceneConstructionData *scene_construction_data, core::GameObjectMemoryLayer *_gameobject_memory_layer,
                       core::IComponentMemoryLayer **_component_memory_layer_array, IEnvironment *_env);

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

        /*!
         * \brief Gets the IEnvironment interface
         * \return A pointer to the IEnvironment, not expected to move in memory during the application lifetime
         */
        IEnvironment* env();

        b2World* get_b2World();

        void doom_scene();
        bool is_doomed();

        Camera* get_camera();

        void set_gravity(sge::Vec2<float> gravity_vec);

        void raycast(RayCastHandler* handler);


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
        b2World* m_b2_world;
        Camera m_camera;

        bool m_doomed_flag = false;
    };
}









#endif //SGE_SCENE_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/




/*!
\file
\brief Header file.
*/