#ifndef FACTORY_EXPERIMENTS_GAMEOBJECT_HPP
#define FACTORY_EXPERIMENTS_GAMEOBJECT_HPP

#include <string>
#include "SGE/Macros.hpp"

#include "SGE/utils/log/Loggable.hpp"
#include "SGE/utils/handles/Handle.hpp"

#include "SGE/components/Transform.hpp"
#include "SGE/components/LogicHub.hpp"

#include "SGE/utils/events/Events.hpp"





namespace sge {
    namespace core {
        class ObjectManager;
    }

    class Scene;

    /*!
     * \brief An object that holds an assortment of components that define its behaviour
     */
    class GameObject : public utils::log::Loggable {
    public:
        explicit GameObject(Scene* scene, const std::string& name = "GameObject");      // TODO: for now it should be fine, but sooner or later this will need a custom copy constructor since its copied on every vector reallocation
        virtual ~GameObject();

        /*!
         * \brief Custom swapping method that allows the swap of two GameObjects (OF THE SAME SCENE)
         * to be swapped in memory without destruction
         * \param other_gameobj The GameObject that needs to be swapped with this one.
         */
        void swap(GameObject& other_gameobj);

        /*!
         * \brief Gets the handle to this GameObject
         * \return An handle to the GameObject
         */
        utils::Handle<GameObject> get_handle();
        /*!
         * \brief Gets the Scene this object is in.
         * \return A pointer to the Scene (which is not expected to be moved in memory until popped)
         */
        Scene* get_scene();

        //region IComponent access and manipulation

        /*!
         * \brief Gets the Transform of this GameObject
         * \return An Handle to the transform, which is expected to be valid until this GameObject is destroyed
         */
        utils::Handle<cmp::Transform>& transform();
        /*!
         * \brief Gets the LogicHub of this GameObject
         * \return An Handle to the LogicHub, which is expected to be valid until this GameObject is destroyed
         */
        utils::Handle<cmp::LogicHub>& logichub();
        /*!
         * \brief Adds a Component to this GameObject
         * \tparam T The type of Component
         * \param id The unique id identifying the type of Component
         * \return An Handle to the newly created Component
         */
        template <class T>
        utils::Handle<T> add_component(const std::string& id);
        /*!
         * \brief Adds a Component to this GameObject without the need to specify the type.
         * \param id The unique id that identifies the type of Component
         * \return The index of the HandleEntry pointing to the newly created Component
         */
        unsigned int add_unspecified_component(const std::string& id);

        /*!
         * \brief Gets a Component attached to this GameObject
         * \tparam T The type of Component
         * \param id The unique id identifying the Component type
         * \return An Handle to the retrieved Component if present, a null Handle if absent.
         */
        template <class T>
        utils::Handle<T> get_component(const std::string& id);
        /*!
         * \brief Checks if a Component is attached to this GameObject
         * \param id The unique id identifying the Component type
         * \return True if the Component is attached to this object, false otherwise
         */
        bool has_component(const std::string& id);
        /*!
         * \brief Dooms a Component, flagging it for removal from this GameObject and destruction
         * \param id The unique id identifying the Component type
         */
        void doom_component(const std::string &id);
        //endregion

        //region Destruction

        /*!
         * \brief Flags this GameObject for destruction. It will be actually destroyed after update and before render.
         */
        void doom();
        /*!
         * \brief Checks if the object is flagged for destruction
         * \return true if this GameObject is flagged for destruction, false otherwise
         */
        bool is_doomed() { return is_doomed_flag; }
        //endregion

        std::string get_string_attached_components();
        std::string get_string_local_hierarchy(bool print_components = false);

    private:
        /*!
         * Pointer to the scene this GameObject is in
         */
        Scene* m_scene;
        /*!
         * \brief The handle referencing this GameObject.
         */
        utils::Handle<GameObject> gameobject_handle;
        utils::Handle<cmp::Transform> transform_handle;
        utils::Handle<cmp::LogicHub> logichub_handle;
        /*!
         * \brief Internal array holding the information necessary to know if the object has a certain component
         * and to retreive an handle to it.
         * \details
         * The information is hold in this format:
         * - at every index of the array is hold the information for the component type given by the correspondence of the ComponentFactory id_to_index
         * - the value at a given index is -1 if the component is absent, if present is equal to the index of the HandleEntry of that component, so the handle can be retrieved
         */
        int m_components_mapped_array[TOTAL_POSSIBLE_COMPONENTS] = {-1};

        bool is_doomed_flag = false;


        unsigned int id_to_index(const std::string& id);
        std::string recursive_get_string_local_hierarchy(std::string &out_str, unsigned int indentation, bool print_components);

        template <class T>
        friend class core::ComponentMemoryLayer;
        friend class core::ObjectManager;
    };



//region Template definitions

    template<class T>
    utils::Handle<T> GameObject::add_component(const std::string &id) {
        if (this->has_component(id)) {
            LOG_ERROR << "Error: this GameObject already has a component of id [" << id << "]";
            exit(1);
        } else {
            unsigned int handle_index = this->add_unspecified_component(id);
            return utils::Handle<T>::get_handle_from_index(handle_index);
        }
    }

    template<class T>
    utils::Handle<T> GameObject::get_component(const std::string &id) {

        if (this->has_component(id)) {
            return utils::Handle<T>::get_handle_from_index(m_components_mapped_array[id_to_index(id)]);
        } else {
            return utils::Handle<T>();     // Returns a null handle.
        }
    }


//endregion

}




#endif //FACTORY_EXPERIMENTS_GAMEOBJECT_HPP





/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/