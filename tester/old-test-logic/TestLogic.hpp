//
// Created by andrea on 5/5/19.
//
#include "SGE/logic/Logic.hpp"
#include "SGE/debug/LineDebugShape.hpp"
#ifndef SGE_HIERARCHYTESTLOGIC_HPP
#define SGE_HIERARCHYTESTLOGIC_HPP

class TestLogic : public sge::Logic {
public:
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_update() override;

private:
    float increaser = 0;
};
#endif //SGE_HIERARCHYTESTLOGIC_HPP
