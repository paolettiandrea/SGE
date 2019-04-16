#ifndef FACTORY_EXPERIMENTS_GAMEOBJECT_HPP
#define FACTORY_EXPERIMENTS_GAMEOBJECT_HPP

#include "handles/Handle.hpp"
#include <string>

class Scene;

class GameObject {
public:
    explicit GameObject(Scene* scene, const std::string& name = "GameObject");
    virtual ~GameObject();

    Handle<GameObject> &get_handle();

    // TEMP
    std::string name;
private:
    /*!
     * Pointer to the scene this GameObject is in
     */
    Scene* scene;
    /*!
     * \brief The handle referencing this GameObject.
     */
    Handle<GameObject> handle;

};


#endif //FACTORY_EXPERIMENTS_GAMEOBJECT_HPP





/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/