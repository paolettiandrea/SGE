#ifndef FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP
#define FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP

#include <vector>
#include "Handle.hpp"
#include "GameObject.hpp"
#include "IComponentMemoryLayer.hpp"
#include "Loggable.hpp"
#include "ComponentFactory.hpp"

namespace sge {
    namespace core {

        /*!
         * \brief Manages a list of Components keeping them contiguous in memory while allowing for creation and removal
         */
        template <class ComponentT>
        class ComponentMemoryLayer : public IComponentMemoryLayer, public utils::log::Loggable {
        public:
            explicit ComponentMemoryLayer(const std::string& id, unsigned int initial_reserved_space = DEFAULT_RESERVED_SPACE_FOR_COMPONENTS);
            /*!
             * \brief Creates a new Component in this ComponentArray
             * \return a handle to the created Component
             */
            utils::Handle<ComponentT> create_new_component(utils::Handle<GameObject> gameobject);

            const std::vector<utils::Handle<ComponentT>> &get_component_vector() const;

            void doom_pass() override;

            unsigned int create_unspecified_component(utils::Handle<GameObject> gameobject) override;
            void remove_unspecified_component(unsigned int index) override;

            void doom_unspecified_component(unsigned int index) override;

        private:
            const std::string id;

            std::vector<ComponentT> component_vector;
            std::vector<utils::Handle<ComponentT>> handle_vector;

            void custom_realloc();

            /*!
             * \brief Removes a Component from this ComponentArray
             * \param target_handle An handle referencing to the Component that needs to be removed
             */
            void remove_component(utils::Handle<ComponentT> target_handle);
        };



        template<class ComponentT>
        ComponentMemoryLayer<ComponentT>::ComponentMemoryLayer(const std::string& _id, unsigned int initial_reserved_space)
                : Loggable("[" + _id + "] COMPONENT MEMORY LAYER")
                , id (_id){
            component_vector.reserve(initial_reserved_space);
            handle_vector.reserve(initial_reserved_space);
        }

        template<class ComponentT>
        utils::Handle<ComponentT> ComponentMemoryLayer<ComponentT>::create_new_component(utils::Handle<GameObject> gameobject) {
            if (component_vector.size()==component_vector.capacity())
                custom_realloc();
            component_vector.emplace_back(gameobject);            // IComponent CONSTRUCTION at the back of the vector
            handle_vector.push_back(component_vector.back().get_handle());     // The pointer will be updated on Component construction

            return handle_vector.back();
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::custom_realloc() {
            component_vector.reserve(component_vector.capacity()*2);

            // Updates the handle entries of every IComponent in the reallocated vector
            for (int i = 0; i < component_vector.size(); ++i) {
                handle_vector[i].update_origin_pointer(&component_vector[i]);
            }

            LOG_DEBUG(18) << "Reallocation happened";
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::remove_component(utils::Handle<ComponentT> target_handle) {
            LOG_DEBUG(25) << "Removing component " << target_handle->get_log_id();
            target_handle->destruction_callback();
            // Sets the correspondent value in the mapped array to -1 (representing absence of the component)
            target_handle->gameobject()->m_components_mapped_array[ComponentFactory::id_to_index(id)] = -1;
            // If we're removing the last element there's no need of memory swapping shenanigans
            // else the last element is swapped in the gap created by the removal and the corresponding handle origin pointer is updated
            if (target_handle.get_pointer() != &component_vector.back()) {
                // Calculate the index of the soon-to-be-removed IComponent in the internal array
                int target_internal_index = target_handle.get_pointer() - &component_vector[0];

                // Swap the last element with the one to remove (for both the vectors since their indexes correspond)
                std::swap(component_vector[target_internal_index], component_vector[component_vector.size()-1]);
                std::swap(handle_vector[target_internal_index], handle_vector[handle_vector.size()-1]);

                // Updates the pointer of the IComponent moved to fill the gap
                handle_vector[target_internal_index].update_origin_pointer(&component_vector[target_internal_index]);
            }
            target_handle.make_origin_expired();
            component_vector.pop_back();
            handle_vector.pop_back();

        }

        template<class ComponentT>
        unsigned int ComponentMemoryLayer<ComponentT>::create_unspecified_component(utils::Handle<GameObject> gameobject) {
            utils::Handle<ComponentT> new_component_handle = create_new_component(gameobject);
            return new_component_handle.get_index();
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::remove_unspecified_component(unsigned int index) {
            auto component = utils::Handle<ComponentT>::get_handle_from_index(index);
            component->doom();
        }

        template<class ComponentT>
        const std::vector<utils::Handle<ComponentT>> &ComponentMemoryLayer<ComponentT>::get_component_vector() const {
            return handle_vector;
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::doom_pass() {
            LOG_DEBUG(25) << "Doom pass";
            unsigned int target_index = 0;
            for (int i = 0; i < handle_vector.size(); ++i) {
                if (handle_vector[target_index]->is_doomed()) {         // IComponent removal
                    remove_component(handle_vector[target_index]);
                } else {
                    target_index++;
                }
            }
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::doom_unspecified_component(unsigned int index) {
            utils::Handle<ComponentT>::get_handle_from_index(index)->doom();
        }
    }
}

#endif //FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP


/*!
\file
\brief Header file.
*/