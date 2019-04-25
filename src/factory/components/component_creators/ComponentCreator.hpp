#ifndef FACTORY_EXPERIMENTS_COMPONENTCREATOR_HPP
#define FACTORY_EXPERIMENTS_COMPONENTCREATOR_HPP


#include <stack>
#include "ComponentMemoryLayer.hpp"
#include "IComponentCreator.hpp"
#include "ComponentFactory.hpp"

/*!
 * \brief Manages a stack of ComponentArray, all of the same Component type.
 * \details Basically contains all the components of a specific type, organized in ComponentArrays which of whom corresponds to a Scene (memory layer).......
 * \tparam T The type of Component co
 */
template <class T>
class ComponentCreator : public IComponentCreator {
public:
    explicit ComponentCreator(const std::string& _id) : id(_id) {
        ComponentFactory::register_component_creator(this);                 // Register itself to the ComponentFactory
    }

    const std::string &get_id() override {
        return id;
    }


    IComponentMemoryLayer* push_new_layer() override {
        componentarray_stack.emplace();
        return &componentarray_stack.top();
    }

    IComponentMemoryLayer* get_top_layer() override {
        return  &componentarray_stack.top();
    }

    void pop_top_layer() override {
        componentarray_stack.pop();
    }

private:
    std::stack<ComponentMemoryLayer<T>> componentarray_stack;
    std::string id;
};
#endif //FACTORY_EXPERIMENTS_COMPONENTCREATOR_HPP
