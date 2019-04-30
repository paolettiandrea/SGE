#ifndef FACTORY_EXPERIMENTS_FACTORY_HPP
#define FACTORY_EXPERIMENTS_FACTORY_HPP

#include "Scene.hpp"
#include <stack>
#include <SGE/components/Path.hpp>
#include "GameObjectMemoryLayer.hpp"
#include "ComponentFactory.hpp"
#include "Subsystem.hpp"
#include "ComponentCreator.hpp"
#include "Transform.hpp"

/*!
 * \brief The object that allows for Scene generation and manipulation.
 * \details
 */
class ObjectManager : public Subsystem {
public:
    ObjectManager()
        : Subsystem("OBJECT MANAGER")
        , transform_creator("Transform")
        , path_creator("Path"){ }
    /*!
     * Builds a new scene at the top of the scene stack
     * \return the index of the built scene in the stack index
     */
    Scene* push_new_scene(Logic* initial_logic);
    /*!
     * \brief Get the Scene that is currently at the top of the stack
     * \return A pointer to the top Scene.
     */
    Scene* get_top_scene();
    /*!
     * \brief Pops the topmost Scene, deleting it.
     */
    void pop_top_scene();
    unsigned int get_scene_stack_size();

    void doom_pass();


private:

    std::stack<Scene> scene_stack;
    std::stack<GameObjectMemoryLayer> gameobj_layers_stack;
    ComponentFactory component_factory;

    ComponentCreator<Transform> transform_creator;
    ComponentCreator<Path> path_creator;
};


#endif //FACTORY_EXPERIMENTS_FACTORY_HPP
