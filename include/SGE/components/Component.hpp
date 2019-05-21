#ifndef FACTORY_EXPERIMENTS_COMPONENT_HPP
#define FACTORY_EXPERIMENTS_COMPONENT_HPP

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
    private:
        utils::Handle<T> this_handle;
    };
}



#endif //FACTORY_EXPERIMENTS_COMPONENT_HPP
