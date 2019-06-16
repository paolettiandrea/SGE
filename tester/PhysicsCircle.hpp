//
// Created by andrea on 6/2/19.
//

#ifndef SGE_PHYSICSCIRCLE_HPP
#define SGE_PHYSICSCIRCLE_HPP

#include "SGE/logic/Logic.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class PhysicsCircle : public sge::Logic {
public:
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_update() override;

    float increaser;
};


#endif //SGE_PHYSICSCIRCLE_HPP
