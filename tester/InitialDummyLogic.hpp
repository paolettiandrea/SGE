//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_INITIALDUMMYLOGIC_HPP
#define FACTORY_EXPERIMENTS_INITIALDUMMYLOGIC_HPP

#include "SGE/logic/Logic.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class InitialDummyLogic : public Logic {
public:
    std::string get_logic_id() override;

    void on_start() override;

};




#endif //FACTORY_EXPERIMENTS_INITIALDUMMYLOGIC_HPP
