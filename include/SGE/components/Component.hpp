#ifndef FACTORY_EXPERIMENTS_COMPONENT_HPP
#define FACTORY_EXPERIMENTS_COMPONENT_HPP

//#include "SGE/GameObject.hpp"
#include "SGE/utils/handles/Handle.hpp"
#include "SGE/utils/log/Loggable.hpp"


class GameObject;

/*!
 * \brief An aggregation of related data and functionality meant to be attached
 * to a GameObject in order to have an impact on its behaviour
 */
class Component : public utils::log::Loggable {
public:
    explicit Component(Handle<GameObject> gameobject, const std::string &id);

    Handle<GameObject> &gameobject();

    /*!
     * \brief A callback called right before the removal of the component,
     * a concrete component can override this in order to prepare for deletion
     */
    virtual void destruction_callback() {}

    bool is_doomed() { return is_doomed_flag; }
    void doom();


private:
    Handle<GameObject> gameobject_handle;

    bool is_doomed_flag = false;

    template <class T>
    friend class ComponentMemoryLayer;

    /*!
     * \brief Flags the Component for destruction
     */
    virtual void destroy();
};


#endif //FACTORY_EXPERIMENTS_COMPONENT_HPP




/*!
\file
\brief Header file.
*/
