#ifndef SGE_PHYSICSSANDBOXENTRY_HPP
#define SGE_PHYSICSSANDBOXENTRY_HPP

#include "SGE/logic/Logic.hpp"

class PhysicsSandboxEntry : public sge::Logic {
public:
    std::string get_logic_type_id() override;

    void on_start() override;
};


#endif //SGE_PHYSICSSANDBOXENTRY_HPP
