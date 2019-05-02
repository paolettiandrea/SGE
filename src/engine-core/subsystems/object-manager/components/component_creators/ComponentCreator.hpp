#ifndef FACTORY_EXPERIMENTS_COMPONENTCREATOR_HPP
#define FACTORY_EXPERIMENTS_COMPONENTCREATOR_HPP


#include <stack>
#include "ComponentMemoryLayer.hpp"
#include "IComponentCreator.hpp"
#include "ComponentFactory.hpp"
#include "Loggable.hpp"

/*!
 * \brief Manages a stack of ComponentArray, all of the same Component type.
 * \details Basically contains all the components of a specific type, organized in ComponentArrays which of whom corresponds to a Scene (memory layer).......
 * \tparam T The type of Component co
 */
template <class T>
class ComponentCreator : public IComponentCreator, public utils::log::Loggable {
public:
    explicit ComponentCreator(const std::string& _id)
        : Loggable("[" + _id + "] COMPONENT CREATOR")
        , id(_id) {
        LOG_DEBUG(15) << "Registering to the ComponentFactory";
        ComponentFactory::register_component_creator(this);                 // Register itself to the ComponentFactory
    }

    const std::string &get_id() override {
        return id;
    }


    IComponentMemoryLayer* push_new_layer() override {
        componentmemorylayer_stack.emplace(id);
        return &componentmemorylayer_stack.top();
    }

    IComponentMemoryLayer* get_unspecified_top_layer() override {
        return  &componentmemorylayer_stack.top();
    }

    ComponentMemoryLayer<T>* get_top_layer() {
        return &componentmemorylayer_stack.top();
    }

    void pop_top_layer() override {
        // Call a destruction_callback on every component of the top layer, since is going to be popped
        for (auto component : componentmemorylayer_stack.top().get_component_vector()) {
            component->destruction_callback();
        }
        componentmemorylayer_stack.pop();
    }

private:
    std::stack<ComponentMemoryLayer<T>> componentmemorylayer_stack;
    std::string id;
};
#endif //FACTORY_EXPERIMENTS_COMPONENTCREATOR_HPP
