#ifndef FACTORY_EXPERIMENTS_ENGINECORE_HPP
#define FACTORY_EXPERIMENTS_ENGINECORE_HPP

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

#include "ObjectManager.hpp"
#include "LogicManager.hpp"
#include "Loggable.hpp"

class EngineCore : utils::log::Loggable {
public:
    EngineCore();
    bool game_loop();

    void initialize(Logic* initial_logic);


private:
    ObjectManager object_manager;
    LogicManager logic_manager;
};


#endif //FACTORY_EXPERIMENTS_ENGINECORE_HPP
