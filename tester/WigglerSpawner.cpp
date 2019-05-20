#include "WigglerSpawner.hpp"
#include "LogBehaviour.hpp"
#include "SGE/debug/PointDebugShape.hpp"
#include "SGE/debug/LineDebugShape.hpp"



std::string WigglerSpawner::get_logic_type_id() {
    return "WigglerSpawner";
}

void WigglerSpawner::on_start() {
    LOG(10) << "on_start";

    for (int i = 0; i < m_number; ++i) {
        auto wiggler_obj = scene()->spawn_gameobject("Wiggler " + std::to_string(i));
        wiggler_obj->logichub()->attach_logic(new Wiggler(0.1+0.01 * i, Vec2<double>(0,0),1*i));

    }



    env()->debug_draw(new debug::PointDebugShape(-238.f, -180.f, 10, "test", 2));


    // FIXME: the factory somehow doesn't complain with an inexistent id!!!

}

void WigglerSpawner::on_update() {
    Logic::on_update();
    angle+=1*env()->delta_time();
    env()->debug_draw(new debug::LineDebugShape(cos(angle) * 500, sin(angle) * 500, 0.f, 0, 0, 2, "test"));
}

