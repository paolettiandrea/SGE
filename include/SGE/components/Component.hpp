#ifndef FACTORY_EXPERIMENTS_COMPONENT_HPP
#define FACTORY_EXPERIMENTS_COMPONENT_HPP

#include "SGE/GameObject.hpp"
#include "SGE/misc/handles/Handle.hpp"


/*!
 * \brief An aggregation of related data and functionality meant to be attached
 * to a GameObject in order to have an impact on its behaviour
 */
class Component {
public:
    explicit Component(Handle<GameObject> gameobject);

    const Handle<GameObject> &gameobject() const;

private:
    Handle<GameObject> gameobject_handle;

};


#endif //FACTORY_EXPERIMENTS_COMPONENT_HPP




/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
