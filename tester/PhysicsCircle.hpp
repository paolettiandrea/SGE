//
// Created by andrea on 6/2/19.
//

#ifndef FACTORY_EXPERIMENTS_PHYSICSCIRCLE_HPP
#define FACTORY_EXPERIMENTS_PHYSICSCIRCLE_HPP

#include "SGE/logic/Logic.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class PhysicsCircle : public sge::Logic {
public:
    std::string get_logic_type_id() override;

    void on_start() override;
};


#endif //FACTORY_EXPERIMENTS_PHYSICSCIRCLE_HPP
