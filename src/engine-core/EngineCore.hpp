#ifndef FACTORY_EXPERIMENTS_ENGINECORE_HPP
#define FACTORY_EXPERIMENTS_ENGINECORE_HPP

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

#include "ObjectManager.hpp"
#include "LogicManager.hpp"
#include "Loggable.hpp"
#include "IEnvironment.hpp"
#include "EngineCore_ConstructionData.hpp"
#include "WindowManager.hpp"

namespace sge::core {
    /*!
     * \brief The internal part of the Engine
     */
    class EngineCore : utils::log::Loggable, IEnvironment {
    public:
        EngineCore(cd::EngineCore_ConstructionData& data);

        virtual ~EngineCore();

        bool game_loop();

        void initialize(cd::SceneConstructionData& initial_scene_cd);

        //region IEnvironment declarations

        double delta_time() override;

    private:
        unsigned int frame_count() override;

    private:
        bool book_new_scene_push(const std::string &name, Logic *initial_logic) override;

        void doom_top_scene() override;
        //double fixed_delta_time() override;
        //endregion


    private:
        ObjectManager object_manager;
        LogicManager logic_manager;
        WindowManager window_manager;

        unsigned int frame_counter = 0;
    };
}





#endif //FACTORY_EXPERIMENTS_ENGINECORE_HPP





/*!
\file
\brief Header file.
*/