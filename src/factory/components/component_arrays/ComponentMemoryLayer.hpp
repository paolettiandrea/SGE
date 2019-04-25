#ifndef FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP
#define FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP

#include <vector>
#include "Handle.hpp"
#include "GameObject.hpp"
#include "IComponentMemoryLayer.hpp"

/*!
 * \brief Manages a list of Components keeping them contiguous in memory while allowing for creation and removal
 */
 template <class ComponentT>
class ComponentMemoryLayer : public IComponentMemoryLayer {
public:
    explicit ComponentMemoryLayer (unsigned int initial_reserved_space=2);
    /*!
     * \brief Creates a new Component in this ComponentArray
     * \return a handle to the created Component
     */
    Handle<ComponentT> create_new_component(Handle<GameObject> gameobject);

    Handle<ComponentT> get_component_by_index(unsigned int index);
    /*!
     * \brief Removes a Component from this ComponentArray
     * \param target_handle An handle refeencing to the Component that needs to be removed
     */
    void remove_component(Handle<ComponentT> target_handle);


    unsigned int create_unspecified_component(Handle<GameObject> gameobject) override;
    void remove_unspecified_component(unsigned int index) override;

private:
    std::vector<ComponentT> component_vector;
    std::vector<Handle<ComponentT>> handle_vector;

    void custom_realloc();
};




template<class ComponentT>
ComponentMemoryLayer<ComponentT>::ComponentMemoryLayer(unsigned int initial_reserved_space) {
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

    // TEMP
    std::cout << "ComponentMemoryLayer of type [" << typeid(ComponentT).name() << "] Reallocation happened" << std::endl;
    //Handle<GameObject>::print_entries_array_info();
}

template<class ComponentT>
void ComponentMemoryLayer<ComponentT>::remove_component(Handle<ComponentT> target_handle) {
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

    /*
    std::cout << "After removal:\n";
    for (int i = 0; i < component_vector.size(); ++i) {
        Handle<GameObject> go = component_vector[i].gameobject();
        std::cout << &component_vector[i] << "----" << go->name << std::endl;
    }
     */
}

template<class ComponentT>
unsigned int ComponentMemoryLayer<ComponentT>::create_unspecified_component(Handle<GameObject> gameobject) {
    Handle<ComponentT> new_component_handle = create_new_component(gameobject);
    return new_component_handle.get_index();
}

template<class ComponentT>
void ComponentMemoryLayer<ComponentT>::remove_unspecified_component(unsigned int index) {
    remove_component(Handle<ComponentT>::get_handle_from_index(index));
}


#endif //FACTORY_EXPERIMENTS_COMPONENTARRAY_HPP






/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/