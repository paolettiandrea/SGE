//
// Created by andrea on 4/30/19.
//

#ifndef SGE_PHYSICSBOX_HPP
#define SGE_PHYSICSBOX_HPP

#include "SGE/logic/Logic.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

class PhysicsBox : public sge::Logic {
public:
    PhysicsBox(float width, float height, bool dynamic = false);
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_destruction() override;

    void on_update() override;

    void on_fixed_update() override;

private:
    float m_width;
    float m_height;
    bool m_dynamic;

private:

};




#endif //SGE_BOXSPAWNER_HPP
