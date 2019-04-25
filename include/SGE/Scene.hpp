#ifndef FACTORY_EXPERIMENTS_SCENE_HPP
#define FACTORY_EXPERIMENTS_SCENE_HPP


#include "SGE/GameObject.hpp"
#include "SGE/misc/handles/Handle.hpp"
#include "SGE/Macros.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class GameObjectMemoryLayer;
class IComponentMemoryLayer;

/*!
 * \brief .....
 */
class Scene {
public:
    /*!
     * \brief The index of this scene in the scene stack, it's not expected to change during the lifetime of the scene.
     */
    const unsigned int index;
    
    explicit Scene(unsigned int _index,
                   GameObjectMemoryLayer* gameobj_memory_layer,
                   IComponentMemoryLayer* componentarrays_array[]);                // ONLY TO BE USED BY THE FACTORY!!!
                   
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

    IComponentMemoryLayer *const *get_component_memorylayer_array() const;


private:
    /*!
     * The GameObject/Component calls to the creation methods of the factory should pass through the scene, so that it can enforce the call only on its index
     */
    GameObjectMemoryLayer* gameobject_memory_layer;
    IComponentMemoryLayer* component_memory_layer_array[TOTAL_POSSIBLE_COMPONENTS];
public:

};


#endif //FACTORY_EXPERIMENTS_SCENE_HPP