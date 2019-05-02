#include "InitialDummyLogic.hpp"
#include "LogBehaviour.hpp"

std::string InitialDummyLogic::get_logic_id() {
    return "InitialDummyLogic";
}

void InitialDummyLogic::on_start() {
    LOG(10) << "on_start";
    gameobject()->add_unspecified_component("Path");


    auto go1 = scene()->spawn_gameobject("Yoo");
    go1->logichub()->attach_logic(new LogBehaviour());

    auto go2 = scene()->spawn_gameobject("Yoo2");
    go2->logichub()->attach_logic(new LogBehaviour());


    go1->doom();

    go2->add_unspecified_component("Padth");        // FIXME: the factory somehow doesn't break with an inexistent id

}

