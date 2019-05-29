//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_BOXSPAWNER_HPP
#define FACTORY_EXPERIMENTS_BOXSPAWNER_HPP

#include "SGE/logic/Logic.hpp"
#include "Wiggler.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class BoxSpawner : public sge::Logic {
public:
    BoxSpawner() {}
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_update() override;

private:
    float angle = 0;

};




#endif //FACTORY_EXPERIMENTS_BOXSPAWNER_HPP
