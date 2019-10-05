#ifndef SGE_COMPONENTCREATOR_HPP
#define SGE_COMPONENTCREATOR_HPP

#include <stack>
#include "ComponentMemoryLayer.hpp"
#include "IComponentCreator.hpp"
#include "ComponentFactory.hpp"
#include "Loggable.hpp"

namespace sge {
    namespace core {

        /*!
         * \brief Manages a stack of ComponentArray, all of the same Component type.
         * \details Basically contains all the components of a specific type, organized in ComponentArrays which of whom corresponds to a Scene (memory layer).......
         * \tparam T The type of Component managed by this ComponentCreator
         */
        template <class T>
        class ComponentCreator : public IComponentCreator, public utils::log::Loggable {
        public:
            /*!
             * \brief Constructor for a ComponentCreator that also registers it to the ComponentFactory
             * \param _id The unique id that will be associated to the Component type managed by this Creator
             */
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

            /*!
             * \brief Gets a pointer to the ComponentMemoryLayer at the top of the stack managed by this ComponentCreator
             */
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

            void ensure_space_comp_vector(unsigned int amount) {
                componentmemorylayer_stack.top().ensure_free_space(amount);
            }

        private:
            std::stack<ComponentMemoryLayer<T>> componentmemorylayer_stack;
            std::string id;
        };
    }
}
#endif //SGE_COMPONENTCREATOR_HPP
