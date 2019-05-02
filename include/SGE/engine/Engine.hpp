#ifndef FACTORY_EXPERIMENTS_ENGINE_HPP
#define FACTORY_EXPERIMENTS_ENGINE_HPP

#include "SGE/utils/log/Loggable.hpp"
#include "SGE/engine/IEnvironment.hpp"

class EngineCore;
class Logic;

/*!
 * \brief The engine object (entry side)
 */
class Engine : public utils::log::Loggable {
public:
    Engine();
    virtual ~Engine();

    bool game_loop();
    IEnvironment* env();


    void initialize(Logic* initial_logic);

private:
    EngineCore* core;
};


#endif //FACTORY_EXPERIMENTS_ENGINE_HPP




/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/