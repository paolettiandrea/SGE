#ifndef SGE_FACTORY_HPP
#define SGE_FACTORY_HPP

#include <stack>

#include "GameObjectMemoryLayer.hpp"
#include "ComponentFactory.hpp"

#include "Subsystem.hpp"

#include "Scene.hpp"
#include "SceneConstructionData.hpp"

#include "Transform.hpp"

namespace sge {
    namespace core {

        /*!
         * \brief The object that manages Scenes, but also indirectly GameObject and Component generation and distruction.
         */
        class ObjectManager : public Subsystem {
            friend class EngineCore;
            friend class EngineCoreDebug;
        public:
            explicit ObjectManager(IEnvironment* _env)
                    : Subsystem("OBJECT MANAGER")
                    , transform_creator("Transform")
                    , env(_env){ }

            virtual ~ObjectManager();

            /*!
             * \brief Books the push of a scene, meaning that if successfull at the end of this gameloop a new scene will
             * be pushed on top of the scene stack with the givel logic
             * \param initial_logic The Logic that will be given to the new Scene
             * \return true if the booking was successfull (because there wasn't already a scene push booked), false otherwise
             */
            bool book_scene_push(const std::string &name, Logic *initial_logic);

            void doom_top_scene();
            /*!
             * Builds a new scene at the top of the scene stack
             * \return the index of the built scene in the stack index
             */
            Scene* push_new_scene(cd::SceneConstructionData *scene_construction_data);
            /*!
             * \brief Get the Scene that is currently at the top of the stack
             * \return A pointer to the top Scene.
             */
            Scene* get_top_scene();
            /*!
             * \brief Pops the topmost Scene, deleting it.
             */
            void pop_top_scene();
            /*!
             * \brief Returns the size of the scene stack on a given moment.
             * \return An unsigned int representing the size of the scene stack a.k.a. the number of existing scenes.
             */
            unsigned int get_scene_stack_size();

            void doom_pass();
            /*!
             * \brief Checks if the scene stack needs to be modified and act accordingly
             * \return true if the scene stack was modified, false otherwise
             */
            bool scene_pass();

            void visual_debug_pass() override;

            std::string get_hierarchy_string();

            std::vector<Transform_H> get_root_transforms();

            std::vector<Transform_H> get_siblings(Transform_H target, bool include_target = false);

            void toggle_visual_debug_transform();
            void toggle_visual_debug_names();

            void memory_buffer_pass() override;

            void doom_scenes(unsigned int number);


        private:
            // counts the number of top scenes that are doomed other than the topmost one
            unsigned int doom_counter;
            std::stack<Scene> scene_stack;
            std::vector<cd::SceneConstructionData> scene_cd_vec;
            std::stack<GameObjectMemoryLayer> gameobj_layers_stack;
            ComponentFactory component_factory;

            ComponentCreator<cmp::Transform> transform_creator;


            IEnvironment* env;

            // Acts as a flag that signals if the push of a new scene was requested during the last gameloop
            cd::SceneConstructionData* new_scene_construction_data = nullptr;


            bool visual_debug_transform_switch = false;
            bool visual_debug_names_switch = false;
        };
    }
}

#endif //SGE_FACTORY_HPP


/*!
\file
\brief Header file.
*/
