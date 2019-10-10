#ifndef SGE_COMPONENT_HPP
#define SGE_COMPONENT_HPP

#include "IComponent.hpp"
#include "SGE/utils/events/Events.hpp"

namespace sge::cmp {
    template <class T>
    class Component : public IComponent {

    public:
        Component(utils::Handle<sge::GameObject> gameobject, const std::string &id)
            : IComponent(gameobject, id)
            {this_handle = utils::Handle<T>::new_entry((T*)this); }

        utils::Handle<T> get_handle () {
            return this_handle;
        }

        /*!
         * \brief Callback triggered AFTER a reallocation of this component
         */
        virtual void reallocation_callback() {}

    private:
        utils::Handle<T> this_handle;




    };
}



#endif //SGE_COMPONENT_HPP
