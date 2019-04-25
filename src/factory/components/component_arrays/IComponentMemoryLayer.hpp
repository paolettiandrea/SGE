#ifndef FACTORY_EXPERIMENTS_ICOMPONENTARRAY_HPP
#define FACTORY_EXPERIMENTS_ICOMPONENTARRAY_HPP

/*!
 * \brief The non-specified interface of a ComponentArray. Allows some manipulations without the need of knowing the exact type of Component that the Array contains.
 */
class IComponentMemoryLayer {
public:
    /*!
     * \brief Creates a new Component of unspecified type in this Array, the exact type of the Array (and it's contained Components) it's hidden behind the interface
     * \param gameobject An handle to the GameObject this component needs to be attached to
     * \return the index of the handle entry referencing to the component, which is guaranteed to stay the same during the Component's lifetime
     */
    virtual unsigned int create_unspecified_component(Handle<GameObject> gameobject) = 0;
    /*!
     * \brief Removes a Component from the array, without the need of knowing the exact type of the Array and the contained Components
     * \param index The index of the handle entry referencing to the Component that needs to be removed
     */
    virtual void remove_unspecified_component(unsigned int index) = 0;
};


#endif //FACTORY_EXPERIMENTS_ICOMPONENTARRAY_HPP
