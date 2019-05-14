#include "WigglerSpawner.hpp"
#include "LogBehaviour.hpp"
#include "SGE/debug/PointDebugShape.hpp"



std::string WigglerSpawner::get_logic_type_id() {
    return "WigglerSpawner";
}

void WigglerSpawner::on_start() {
    LOG(10) << "on_start";
    /*
    for (int i = 0; i < m_number; ++i) {
        auto wiggler = scene()->spawn_gameobject("Wiggler " + std::to_string(i));
        wiggler->logichub()->attach_logic(new Wiggler(0.1+0.01 * i, Vec2<double>(0,0),1*i));
    }

     */

    env()->debug_draw(new debug::PointDebugShape(0,0,2.f));



    // FIXME: the factory somehow doesn't complain with an inexistent id!!!



}

