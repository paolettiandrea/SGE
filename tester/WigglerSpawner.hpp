//
// Created by andrea on 4/30/19.
//

#ifndef FACTORY_EXPERIMENTS_WIGGLERSPAWNER_HPP
#define FACTORY_EXPERIMENTS_WIGGLERSPAWNER_HPP

#include "SGE/logic/Logic.hpp"
#include "Wiggler.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class WigglerSpawner : public sge::Logic {
public:
    WigglerSpawner(int number) : m_number(number) {}
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_update() override;

private:
    int m_number;
    float angle = 0;

};




#endif //FACTORY_EXPERIMENTS_WIGGLERSPAWNER_HPP
