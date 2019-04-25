#ifndef FACTORY_EXPERIMENTS_FACTORY_HPP
#define FACTORY_EXPERIMENTS_FACTORY_HPP

#include "Scene.hpp"
#include <stack>
#include "gameobjects/GameObjectMemoryLayer.hpp"
#include "ComponentFactory.hpp"

/*!
 * The object used to build GameObjects and Components
 */
class Factory {
public:
    /*!
     * Builds a new scene at the top of the scene stack
     * \return the index of the built scene in the stack index
     */
    Scene* push_new_scene();
    /*!
     * \brief Get the Scene that is currently at the top of the stack
     * \return A pointer to the top Scene.
     */
    Scene* get_top_scene();
    /*!
     * \brief Pops the topmost Scene, deleting it.
     */
    void pop_top_scene();


private:
    std::stack<Scene> scene_stack;

    std::stack<GameObjectMemoryLayer> gameobj_layers_stack;
    ComponentFactory component_factory;
};


#endif //FACTORY_EXPERIMENTS_FACTORY_HPP
