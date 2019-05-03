#ifndef FACTORY_EXPERIMENTS_LOGIC_HPP
#define FACTORY_EXPERIMENTS_LOGIC_HPP

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

        virtual std::string get_logic_type_id() = 0;
        utils::Handle<GameObject> gameobject();
        Scene* scene();
        IEnvironment* env();


        // Logic Callbacks ------------------------------------------------------------------------------------------------

        void on_start() override;
        void on_destruction() override;

        void on_update() override;
        void on_fixed_update() override;

    private:
        utils::Handle<GameObject> m_gameobject_handle;
        Scene* m_scene;
        IEnvironment* m_env;

    };
}




#endif //FACTORY_EXPERIMENTS_LOGIC_HPP


/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
