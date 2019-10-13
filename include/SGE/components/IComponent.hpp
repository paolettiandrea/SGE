#ifndef SGE_ICOMPONENT_HPP
#define SGE_ICOMPONENT_HPP

//#include "SGE/GameObject.hpp"
#include "SGE/utils/handles/Handle.hpp"
#include "SGE/utils/log/Loggable.hpp"
#include "SGE/utils/events/Events.hpp"

namespace sge {

    class GameObject;

    namespace core {
        template <class T>
        class ComponentMemoryLayer;
    }

    namespace cmp {
        /*!
         * \brief An aggregation of related data and functionality meant to be attached
         * to a GameObject in order to have an impact on a specific aspect of its behaviour
         */
        class IComponent : public utils::log::Loggable {
        public:
            /*!
             * \brief Event called right before the removal and destruction of a Component
             */
            utils::event::Event removal_event;

            /*!
             * \brief Constructor meant to be used only by the factory
             * \param gameobject An handle to the GameObject this Component needs to be attached to
             * \param id The id that identifies the univocally the type of component
             */
            explicit IComponent(utils::Handle<sge::GameObject> gameobject, const std::string &id);

            /*!
             * \brief Gets an handle to the GameObject this Component is attached to
             */
            utils::Handle<sge::GameObject> gameobject();

            /*!
             * \brief Gets an handle to the GameObject this Component is attached to
             */
            utils::Handle<sge::GameObject> gameobject() const;
            /*!
             * \brief A callback called right before the removal of the component,
             * a concrete component can override this in order to prepare for deletion
             */
            virtual void destruction_callback() { removal_event(); }

            /*!
             * \brief Checks if this Component is doomed
             * \return true if the Component is doomed and needs to be destroyed on the next doom_pass(), false otherwise
             */
            bool is_doomed() { return is_doomed_flag; }
            /*!
             * \brief Dooms this Component, the actual destruction will be delayed to after the fixed_update and before render
             */
            void doom();

        private:
            utils::Handle<sge::GameObject> gameobject_handle;
            bool is_doomed_flag = false;

            template <class T>
            friend class core::ComponentMemoryLayer;

        };
    }
}


#endif //SGE_ICOMPONENT_HPP




/*!
\file
\brief Header file.
*/
