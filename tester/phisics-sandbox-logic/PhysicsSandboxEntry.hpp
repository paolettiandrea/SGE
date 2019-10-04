#ifndef SGE_PHYSICSSANDBOXENTRY_HPP
#define SGE_PHYSICSSANDBOXENTRY_HPP

#include "SGE/logic/Logic.hpp"

class PhysicsSandboxEntry : public sge::Logic {
public:
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_update() override;

private:
    void spawn_bouncer(const std::string& name);

    float accumulator;
    int bouncer_counter;
};


#endif //SGE_PHYSICSSANDBOXENTRY_HPP
