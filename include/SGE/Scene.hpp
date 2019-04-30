#ifndef FACTORY_EXPERIMENTS_SCENE_HPP
#define FACTORY_EXPERIMENTS_SCENE_HPP


#include "SGE/GameObject.hpp"
#include "SGE/Macros.hpp"
#include "SGE/utils/handles/Handle.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class GameObjectMemoryLayer;
class IComponentMemoryLayer;

/*!
 * \brief .....
 */
class Scene : public utils::log::Loggable {
public:
    /*!
     * \brief The index of this scene in the scene stack, it's not expected to change during the lifetime of the scene.
     */
    const unsigned int index;
    
    explicit Scene(unsigned int _index,
                   GameObjectMemoryLayer* gameobj_memory_layer,
                   IComponentMemoryLayer* componentarrays_array[],
                   Logic* initial_logic);                // ONLY TO BE USED BY THE FACTORY!!!

    virtual ~Scene();

    /*!
     * \brief Spawns a new GameObject in this Scene
     * \return an Handle referencing to the spawn GameObject
     */
    Handle<GameObject> spawn_gameobject(const std::string& name);
    /*!
     * \brief Flags an object for destruction
     * \param target_handle An handle to the GameObject that needs to be destroyed
     */
    void destroy_gameobject(Handle<GameObject> target_handle);
    /*!
     * \brief Gets an array of pointers to every ComponentMemoryLayer of this scene, one for each type at the index
     * expected from the id_to_index correspondence
     */
    IComponentMemoryLayer *const *get_component_memorylayer_array() const;


private:
    /*!
     * \brief The GameObject/Component calls to the creation methods of the factory should pass through the scene, so that it can enforce the call only on its index
     */
    GameObjectMemoryLayer* gameobject_memory_layer;
    /*!
     * \brief Array of pointers to each ComponentMemoryLayer (unspecified interface) of this Scene, one for each type
     * at the index expected from the id_to_index correspondance
     */
    IComponentMemoryLayer* component_memory_layer_array[TOTAL_POSSIBLE_COMPONENTS];
};


#endif //FACTORY_EXPERIMENTS_SCENE_HPP
