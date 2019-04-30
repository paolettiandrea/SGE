//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_ENGINE_HPP
#define FACTORY_EXPERIMENTS_ENGINE_HPP

#include "SGE/utils/log/Loggable.hpp"

class EngineCore;
class Logic;
/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
/*!
 * \brief The engine object (entry side)
 */
class Engine : public utils::log::Loggable {
public:
    Engine();
    virtual ~Engine();

    bool game_loop();

    void initialize(Logic* initial_logic);

private:
    EngineCore* core;
};


#endif //FACTORY_EXPERIMENTS_ENGINE_HPP
