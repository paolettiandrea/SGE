#ifndef FACTORY_EXPERIMENTS_COMPONENT_HPP
#define FACTORY_EXPERIMENTS_COMPONENT_HPP

//#include "SGE/GameObject.hpp"
#include "SGE/utils/handles/Handle.hpp"
#include "SGE/utils/log/Loggable.hpp"

namespace sge {

    class GameObject;

    namespace core {
        template <class T>
        class ComponentMemoryLayer;
    }

/*!
 * \brief An aggregation of related data and functionality meant to be attached
 * to a GameObject in order to have an impact on its behaviour
 */
    class Component : public utils::log::Loggable {
    public:
        explicit Component(utils::Handle<sge::GameObject> gameobject, const std::string &id);

        utils::Handle<sge::GameObject> &gameobject();

        /*!
         * \brief A callback called right before the removal of the component,
         * a concrete component can override this in order to prepare for deletion
         */
        virtual void destruction_callback() {}

        bool is_doomed() { return is_doomed_flag; }
        void doom();


    private:
        utils::Handle<sge::GameObject> gameobject_handle;

        bool is_doomed_flag = false;

        template <class T>
        friend class core::ComponentMemoryLayer;

        /*!
         * \brief Flags the Component for destruction
         */
        virtual void destroy();
    };

}


#endif //FACTORY_EXPERIMENTS_COMPONENT_HPP




/*!
\file
\brief Header file.
*/
