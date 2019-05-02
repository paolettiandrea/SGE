#ifndef FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP
#define FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP

#include <vector>
#include "Handle.hpp"
#include "GameObject.hpp"
#include "IComponentMemoryLayer.hpp"
#include "Loggable.hpp"
#include "ComponentFactory.hpp"

/*!
 * \brief Manages a list of Components keeping them contiguous in memory while allowing for creation and removal
 */
 template <class ComponentT>
class ComponentMemoryLayer : public IComponentMemoryLayer, public utils::log::Loggable {
public:
    explicit ComponentMemoryLayer(const std::string& id, unsigned int initial_reserved_space = 16);
    /*!
     * \brief Creates a new Component in this ComponentArray
     * \return a handle to the created Component
     */
    Handle<ComponentT> create_new_component(Handle<GameObject> gameobject);

    Handle<ComponentT> get_component_by_index(unsigned int index);


    const std::vector<Handle<ComponentT>> &get_component_vector() const;

    void doom_pass() override;

    unsigned int create_unspecified_component(Handle<GameObject> gameobject) override;
    void remove_unspecified_component(unsigned int index) override;

    void doom_unspecified_component(unsigned int index) override;

private:
    const std::string id;

    std::vector<ComponentT> component_vector;
    std::vector<Handle<ComponentT>> handle_vector;

    void custom_realloc();

    /*!
     * \brief Removes a Component from this ComponentArray
     * \param target_handle An handle referencing to the Component that needs to be removed
     */
    void remove_component(Handle<ComponentT> target_handle);
};



template<class ComponentT>
ComponentMemoryLayer<ComponentT>::ComponentMemoryLayer(const std::string& _id, unsigned int initial_reserved_space)
    : Loggable("[" + _id + "] COMPONENT MEMORY LAYER")
    , id (_id){
    component_vector.reserve(initial_reserved_space);
    handle_vector.reserve(initial_reserved_space);
}

template<class ComponentT>
Handle<ComponentT> ComponentMemoryLayer<ComponentT>::create_new_component(Handle<GameObject> gameobject) {
    if (component_vector.size()==component_vector.capacity())
        custom_realloc();

    component_vector.emplace_back(gameobject);                      // Component CONSTRUCTION at the back of the vector
    handle_vector.push_back(Handle<ComponentT>::new_entry(&component_vector.back()));
    return handle_vector.back();
}

template<class ComponentT>
void ComponentMemoryLayer<ComponentT>::custom_realloc() {
    component_vector.reserve(component_vector.capacity()*2);

    // Updates the handle entries of every Component in the reallocated vector
    for (int i = 0; i < component_vector.size(); ++i) {
        handle_vector[i].update_origin_pointer(&component_vector[i]);
    }

    LOG_DEBUG(18) << "Reallocation happened";
}

template<class ComponentT>
void ComponentMemoryLayer<ComponentT>::remove_component(Handle<ComponentT> target_handle) {
    LOG_DEBUG(25) << "Removing component " << target_handle->get_log_id();
    target_handle->destruction_callback();
    // Sets the correspondent value in the mapped array to -1 (representing absence of the component)
    target_handle->gameobject()->m_components_mapped_array[ComponentFactory::id_to_index(id)] = -1;
    // If we're removing the last element there's no need of memory swapping shenanigans
    // else the last element is swapped in the gap created by the removal and the corresponding handle origin pointer is updated
    if (target_handle.get_pointer() != &component_vector.back()) {
        // Calculate the index of the soon-to-be-removed Component in the internal array
        int target_internal_index = target_handle.get_pointer() - &component_vector[0];

        // Swap the last element with the one to remove (for both the vectors since their indexes correspond)
        std::swap(component_vector[target_internal_index], component_vector[component_vector.size()-1]);
        std::swap(handle_vector[target_internal_index], handle_vector[handle_vector.size()-1]);

        // Updates the pointer of the Component moved to fill the gap
        handle_vector[target_internal_index].update_origin_pointer(&component_vector[target_internal_index]);
    }
    target_handle.make_origin_expired();
    component_vector.pop_back();
    handle_vector.pop_back();

}

template<class ComponentT>
unsigned int ComponentMemoryLayer<ComponentT>::create_unspecified_component(Handle<GameObject> gameobject) {
    Handle<ComponentT> new_component_handle = create_new_component(gameobject);
    return new_component_handle.get_index();
}

template<class ComponentT>
void ComponentMemoryLayer<ComponentT>::remove_unspecified_component(unsigned int index) {
    auto component = Handle<ComponentT>::get_handle_from_index(index);
    component->destroy();
}

template<class ComponentT>
const std::vector<Handle<ComponentT>> &ComponentMemoryLayer<ComponentT>::get_component_vector() const {
    return handle_vector;
}

template<class ComponentT>
void ComponentMemoryLayer<ComponentT>::doom_pass() {
    LOG_DEBUG(25) << "Doom pass";
    unsigned int target_index = 0;
    for (int i = 0; i < handle_vector.size(); ++i) {
        if (handle_vector[target_index]->is_doomed()) {         // Component removal
            remove_component(handle_vector[target_index]);
        } else {
            target_index++;
        }
    }
}

template<class ComponentT>
void ComponentMemoryLayer<ComponentT>::doom_unspecified_component(unsigned int index) {
    Handle<ComponentT>::get_handle_from_index(index)->doom();
}


#endif //FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP


/*!
\file
\brief Header file.
*/