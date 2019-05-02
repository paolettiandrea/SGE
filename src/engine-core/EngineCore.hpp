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

class EngineCore : utils::log::Loggable, IEnvironment {
public:
    EngineCore();
    bool game_loop();

    void initialize(Logic* initial_logic);

    //region IEnvironment declarations

    double delta_time() override;

private:
    bool book_new_scene_push(const std::string &name, Logic *initial_logic) override;

    void doom_top_scene() override;
    //double fixed_delta_time() override;
    //endregion


private:
    ObjectManager object_manager;
    LogicManager logic_manager;
};


#endif //FACTORY_EXPERIMENTS_ENGINECORE_HPP
