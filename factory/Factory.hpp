#ifndef FACTORY_EXPERIMENTS_FACTORY_HPP
#define FACTORY_EXPERIMENTS_FACTORY_HPP

#include "../Scene.hpp"
#include <stack>

/*!
 * The object used to build GameObjects and Components
 */
class Factory {
public:
    /*!
     * Builds a new scene at the top of the scene stack
     * \return the index of the built scene in the stack index
     */
    unsigned int build_scene();

    Scene* get_top_scene();


private:
    std::stack<Scene> scene_stack;
};


#endif //FACTORY_EXPERIMENTS_FACTORY_HPP
