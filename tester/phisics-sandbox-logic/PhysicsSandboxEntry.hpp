#ifndef SGE_PHYSICSSANDBOXENTRY_HPP
#define SGE_PHYSICSSANDBOXENTRY_HPP

#include "SGE/logic/Logic.hpp"
#include <SGE/components/physics/Rigidbody.hpp>


class PhysicsSandboxEntry : public sge::Logic {
public:
    std::string get_logic_type_id() override;

    void on_start() override;

    void on_update() override;

    void on_fixed_update() override;


private:
    void spawn_bouncer(const std::string& name);
    utils::Handle<sge::GameObject> static_wall;
    utils::Handle<sge::cmp::Rigidbody> rb;

    float accumulator;
    int bouncer_counter;
};


#endif //SGE_PHYSICSSANDBOXENTRY_HPP
