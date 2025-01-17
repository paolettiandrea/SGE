#ifndef SGE_GAMEOBJECTMEMORYLAYER_HPP
#define SGE_GAMEOBJECTMEMORYLAYER_HPP

#include <vector>
#include "SGE/GameObject.hpp"
#include "Handle.hpp"
#include "Loggable.hpp"

namespace sge {

    class Scene;

    namespace core {

        /*!
         * \brief It's the object meant to manage a scene's list of GameObjects in memory
         * \details
         * It has a few functions:
         * - allowing for GameObject creation and destruction
         * - update of the handle pointers when necessary (since it will move objects in the underlying array during creation and removal)
         */
        class GameObjectMemoryLayer : public utils::log::Loggable {
        public:
            explicit GameObjectMemoryLayer(unsigned int initial_reserved_spaces = 16);  // TODO: change default to a reasonable number
            /*!
             * \brief Creates a new GameObject in this memory layer
             * \return a handle to the created GameObject
             */
            utils::Handle<GameObject> create_new_gameobject(const std::string& name, Scene* scene);
            /*!
             * Removes a GameObject from this memory layer
             * \param target_handle An handle to the GameObject that needs to be removed
             */
            bool remove_gameobject(utils::Handle<GameObject> target_handle);

            std::vector<GameObject>* get_gameobjects_vector();

            void doom_pass();

        private:
            /*!
             * \brief Method that is called right before a normal reallocation would happen, it reallocates at the same way but it also updates the handle's pointers to the objects since they've been moved in memory.
             */
            void custom_realloc();
            /*!
             * \brief The internal vector of GameObjects
             */
            std::vector<GameObject> gameobjects_vector;

        };

    }


}


#endif //SGE_GAMEOBJECTMEMORYLAYER_HPP



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/