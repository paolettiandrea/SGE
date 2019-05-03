//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_LOGBEHAVIOUR_HPP
#define FACTORY_EXPERIMENTS_LOGBEHAVIOUR_HPP

#include "SGE/logic/Logic.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class LogBehaviour : public sge::Logic {
public:
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_destruction() override;

    void on_update() override;

    void on_fixed_update() override;
};




#endif //FACTORY_EXPERIMENTS_INITIALDUMMYLOGIC_HPP
