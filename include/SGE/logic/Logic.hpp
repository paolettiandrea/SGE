#ifndef SGE_LOGIC_HPP
#define SGE_LOGIC_HPP

#include <string>

#include "SGE/GameObject.hpp"
#include "SGE/Scene.hpp"

#include "SGE/logic/ILogicCallbacks.hpp"

#include "SGE/utils/handles/Handle.hpp"
#include "SGE/utils/log/Loggable.hpp"

namespace sge {
    /*!
     * \brief Object through which the library user can define it's custom game logic.
     */
    class Logic : public ILogicCallbacks, public utils::log::Loggable {
    public:
        Logic() : Loggable("Placeholder id for Logic yet to be attached") {

        }
        virtual ~Logic();

        /*!
         * \brief Method called on attachment to update the environment references of this Logic object
         * \param gameobj An handle to the gameobject this object will be attached to from now
         */
        void update_references(utils::Handle<GameObject> gameobj);
        /*!
         * \brief Method that effectivelly defines the unique logic_type_id for a Logic object
         * \return The unique logic_type_id
         */
        virtual std::string get_logic_id() = 0;
        /*!
         * \brief Gets an handle to the GameObject this Logic is attached to
         * \return An Handle to the GameObject
         */
        utils::Handle<GameObject> gameobject();
        /*!
         * \brief Gets the Scene this Logic's GameObject is attached to.
         * \return A pointer to the Scene, which is not expected to move in memory until popped.
         */
        Scene* scene();
        /*!
         * \brief Gets the IEnvironment interface, that allows for direct queries to the engine.
         * \return A pointer to the IEnvironment, which is not expected to move in memory during the application lifetime
         */
        IEnvironment* env();

        virtual std::string debug_string() { return std::string(); }


        // Logic Callbacks ------------------------------------------------------------------------------------------------

        void on_start() override {}
        void on_destruction() override {}
        void on_scene_destruction() override {}

        void on_update() override {}
        void on_fixed_update() override {}

        void on_scene_pause() override {}

        void on_scene_resume() override {}

        void on_collision_begin(CollisionInfo &collision_info) override {}
        void on_collision_end(CollisionInfo &collision_info) override {}

        void pre_solve(b2Contact *contact, const b2Manifold *oldManifold, const CollisionInfo &info) override {}
        void post_solve(b2Contact *contact, const b2ContactImpulse *impulse, const CollisionInfo &info) override {}

        void doom();
        bool is_doomed();

    private:
        utils::Handle<GameObject> m_gameobject_handle;
        Scene* m_scene;
        IEnvironment* m_env;
        bool is_doomed_flag = false;

    };
}




#endif //SGE_LOGIC_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
