#ifndef SGE_ICOMPONENTARRAY_HPP
#define SGE_ICOMPONENTARRAY_HPP

namespace sge::core {

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
        virtual unsigned int create_unspecified_component(utils::Handle<GameObject> gameobject) = 0;
        /*!
         * \brief Removes a Component from the array, without the need of knowing the exact type of the Array and the contained Components
         * \param index The index of the handle entry referencing to the Component that needs to be removed
         */
        virtual void remove_unspecified_component(unsigned int index) = 0;
        /*!
         * \brief Dooms an unspecified component, flagging it for destruction.
         * \param index
         */
        virtual void doom_unspecified_component(unsigned int index) = 0;
        /*!
         * \brief Destroy every doomed component
         */
        virtual void doom_pass() = 0;

        virtual void memory_buffer_pass() = 0;

        virtual void destruction_callback_pass() = 0;

    };
}




#endif //SGE_ICOMPONENTARRAY_HPP
