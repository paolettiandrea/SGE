//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_LOGICMANAGER_HPP
#define FACTORY_EXPERIMENTS_LOGICMANAGER_HPP

#include "Subsystem.hpp"
#include "ComponentCreator.hpp"
#include "LogicHub.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class LogicManager : public Subsystem {
public:
    LogicManager();

    void on_update();
    void on_fixed_update();

private:
    ComponentCreator<LogicHub> logichub_creator;
};


#endif //FACTORY_EXPERIMENTS_LOGICMANAGER_HPP
