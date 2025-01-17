#ifndef SGE_COMPONENTARRAY_HPP
#define SGE_COMPONENTARRAY_HPP

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
            explicit ComponentMemoryLayer(const std::string& id);
            /*!
             * \brief Creates a new Component in this ComponentArray
             * \return a handle to the created Component
             */
            utils::Handle<ComponentT> create_new_component(utils::Handle<GameObject> gameobject);

            std::vector<utils::Handle<ComponentT>> get_component_vector();

            void doom_pass() override;
            void destruction_callback_pass() override;

            void memory_buffer_pass() override;


            unsigned int create_unspecified_component(utils::Handle<GameObject> gameobject) override;
            void remove_unspecified_component(unsigned int index) override;

            void doom_unspecified_component(unsigned int index) override;

        private:
            const std::string id;

            std::vector<ComponentT> component_vector;
            std::vector<utils::Handle<ComponentT>> handle_vector;

            void custom_realloc(unsigned int new_capacity);

            /*!
             * \brief Removes a Component from this ComponentArray
             * \param target_handle An handle referencing to the Component that needs to be removed
             */
            bool remove_component(utils::Handle<ComponentT> target_handle);
        };

        template<class ComponentT>
        ComponentMemoryLayer<ComponentT>::ComponentMemoryLayer(const std::string& _id)
                : Loggable("[" + _id + "] COMPONENT MEMORY LAYER")
                , id (_id){
            component_vector.reserve(SGE_COMPONENT_MEMORY_BUFFER_SIZE*2);
            handle_vector.reserve(SGE_COMPONENT_MEMORY_BUFFER_SIZE*2);
        }

        template<class ComponentT>
        utils::Handle<ComponentT> ComponentMemoryLayer<ComponentT>::create_new_component(utils::Handle<GameObject> gameobject) {

            if (component_vector.capacity()>component_vector.size()){
                component_vector.emplace_back(gameobject);            // IComponent CONSTRUCTION at the back of the vector
                handle_vector.push_back(component_vector.back().get_handle());     // The pointer will be updated on Component construction
                component_vector.back().initialization_callback();
            } else {
                LOG_ERROR << "Tried to create a new component but the memory buffer( for this frame ()"
                          << SGE_COMPONENT_MEMORY_BUFFER_SIZE << ") for this frame is full.\n"
                          << "A new addition would cause a reallocation, which could be fatal if performed during some"
                             "component callback (like on_update)";
                exit(1);
            }
            return handle_vector.back();
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::custom_realloc(unsigned int new_capacity) {
            if (new_capacity>component_vector.capacity()) {

                component_vector.reserve(new_capacity);
                // Updates the handle entries of every IComponent in the reallocated vector
                for (int i = 0; i < component_vector.size(); ++i) {
                    handle_vector[i].update_origin_pointer(&component_vector[i]);
                    component_vector[i].reallocation_callback();
                }

                LOG_DEBUG(18) << "Reallocation happened";
            } else {
                LOG_ERROR << "On custom reallocation the new_capacity value that was given ["
                          << new_capacity << "] is smaller than the current component vector capacity ["
                          << component_vector.capacity() << "]";
                exit(1);
            }
        }

        template<class ComponentT>
        bool ComponentMemoryLayer<ComponentT>::remove_component(utils::Handle<ComponentT> target_handle) {
            bool swap_happened = false;
            LOG_DEBUG(25) << "Removing component " << target_handle->get_log_id();
             // Sets the correspondent value in the mapped array to -1 (representing absence of the component)
            target_handle->gameobject()->m_components_mapped_array[ComponentFactory::id_to_index(id)] = -1;

            // If we're removing the last element there's no need of memory swapping shenanigans
            // else the last element is swapped in the gap created by the removal and the corresponding handle origin pointer is updated
            if (target_handle.get_pointer() != &component_vector.back()) {
                LOG_DEBUG(32) << "Removing in the middle of the vector, so the element at the back ["
                              << &component_vector.back() << "] was moved to [" << target_handle.get_pointer() << "]";

                // Calculate the index of the soon-to-be-removed IComponent in the internal array
                int target_internal_index = target_handle.get_pointer() - &component_vector[0];

                // Swap the last element with the one to remove (for both the vectors since their indexes correspond)
                std::swap(component_vector[target_internal_index], component_vector[component_vector.size()-1]);
                std::swap(handle_vector[target_internal_index], handle_vector[handle_vector.size()-1]);

                // Updates the pointer of the IComponent moved to fill the gap
                handle_vector[target_internal_index].update_origin_pointer(&component_vector[target_internal_index]);
                handle_vector[target_internal_index]->reallocation_callback();          // Trigger on the moved object a realloc callback

                swap_happened = true;
            }
            target_handle.make_origin_expired();
            component_vector.pop_back();
            handle_vector.pop_back();
            return swap_happened;
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
        std::vector<utils::Handle<ComponentT>> ComponentMemoryLayer<ComponentT>::get_component_vector() {
            return handle_vector;
        }

        /**
         * /brief Remove all the doomed Components of this ComponentMemoryLayer
    */
        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::doom_pass() {
            LOG_DEBUG(25) << "Doom pass";
            for (int i = 0; i < handle_vector.size(); ++i) {
                if (handle_vector[i]->is_doomed()) {         // IComponent removal
                    auto comp_removed = remove_component(handle_vector[i]);
                    if (comp_removed) i--;
                }
            }
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::doom_unspecified_component(unsigned int index) {
            utils::Handle<ComponentT>::get_handle_from_index(index)->doom();
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::memory_buffer_pass() {
            if ((component_vector.capacity() - component_vector.size()) < SGE_COMPONENT_MEMORY_BUFFER_SIZE) {
                custom_realloc(component_vector.capacity() * 2);
            }
        }

        template<class ComponentT>
        void ComponentMemoryLayer<ComponentT>::destruction_callback_pass() {
            for (int i = 0; i < handle_vector.size(); ++i) {
                if (handle_vector[i]->is_doomed()) {
                    handle_vector[i]->destruction_callback();
                }
            }
        }
    }
}

#endif //SGE_COMPONENTARRAY_HPP