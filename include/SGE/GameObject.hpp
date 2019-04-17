#ifndef FACTORY_EXPERIMENTS_GAMEOBJECT_HPP
#define FACTORY_EXPERIMENTS_GAMEOBJECT_HPP

#include "Handle.hpp"
#include <string>

class Scene;

class GameObject {
public:
    explicit GameObject(Scene* scene, const std::string& name = "GameObject");                  // TODO: for now it should be fine, but sooner or later this will need a copy constructor
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