#ifndef FACTORY_EXPERIMENTS_GAMEOBJECT_HPP
#define FACTORY_EXPERIMENTS_GAMEOBJECT_HPP



#include <string>
#include "SGE/Macros.hpp"
#include "SGE/components/Transform.hpp"
#include "SGE/components/LogicHub.hpp"
#include "SGE/utils/log/Loggable.hpp"
#include "SGE/utils/handles/Handle.hpp"

class Scene;

class GameObject : public utils::log::Loggable {
public:


    explicit GameObject(Scene* scene, const std::string& name = "GameObject");      // TODO: for now it should be fine, but sooner or later this will need a custom copy constructor since its copied on every vector reallocation
    virtual ~GameObject();


    Handle<GameObject> &get_handle();

    const Handle<Transform> &transform() const;
    Handle<LogicHub> &logichub();

    template <class T>
    Handle<T> add_component(const std::string& id);
    template <class T>
    Handle<T> get_component(const std::string& id);
    bool has_component(const std::string& id);
    void remove_component(const std::string& id);


private:
    /*!
     * Pointer to the scene this GameObject is in
     */
    Scene* scene;
    /*!
     * \brief The handle referencing this GameObject.
     */
    Handle<GameObject> gameobject_handle;
    Handle<Transform> transform_handle;
    Handle<LogicHub> logichub_handle;
    /*!
     * \brief Internal array holding the information necessary to know if the object has a certain component
     * and to retreive an handle to it.
     */
    int my_components_mapped_array[TOTAL_POSSIBLE_COMPONENTS] = {-1};


    unsigned int add_unspecified_component(const std::string& id);
    unsigned int id_to_index(const std::string& id);

};


template<class T>
Handle<T> GameObject::add_component(const std::string &id) {
    LOG_DEBUG(19) << "Adding a new component of id [" + id + "]";
    if (this->has_component(id)) {
        LOG_ERROR << "Error: this GameObject already has a component of id [" << id << "]";
        exit(1);
    } else {
        unsigned int handle_index = this->add_unspecified_component(id);
        return Handle<T>::get_handle_from_index(handle_index);
    }
}

template<class T>
Handle<T> GameObject::get_component(const std::string &id) {

    if (this->has_component(id)) {
        return Handle<T>::get_handle_from_index(my_components_mapped_array[id_to_index(id)]);
    } else {
        return Handle<T>();     // Returns a null handle.
    }
}




#endif //FACTORY_EXPERIMENTS_GAMEOBJECT_HPP





/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/