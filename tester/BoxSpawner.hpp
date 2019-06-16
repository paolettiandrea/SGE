#ifndef SGE_BOXSPAWNER_HPP
#define SGE_BOXSPAWNER_HPP

#include "SGE/logic/Logic.hpp"
#include "Wiggler.hpp"

class BoxSpawner : public sge::Logic {
public:
    BoxSpawner() {}
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_update() override;

private:
    float angle = 0;
    float m_increaser = 0.f;

    utils::Handle<GameObject> parent_go;
    utils::Handle<GameObject> child_go;
    utils::Handle<GameObject> child_child_go;

};

#endif //SGE_BOXSPAWNER_HPP



/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/