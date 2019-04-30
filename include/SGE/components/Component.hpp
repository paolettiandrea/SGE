#ifndef FACTORY_EXPERIMENTS_COMPONENT_HPP
#define FACTORY_EXPERIMENTS_COMPONENT_HPP

//#include "SGE/GameObject.hpp"
#include "SGE/misc/handles/Handle.hpp"
#include "Loggable.hpp"


class GameObject;

/*!
 * \brief An aggregation of related data and functionality meant to be attached
 * to a GameObject in order to have an impact on its behaviour
 */
class Component : public utils::log::Loggable {
public:
    explicit Component(Handle<GameObject> gameobject, const std::string &id);

    Handle<GameObject> &gameobject();

private:
    Handle<GameObject> gameobject_handle;

};


#endif //FACTORY_EXPERIMENTS_COMPONENT_HPP




/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
