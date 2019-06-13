#include "BoxSpawner.hpp"
#include "PhysicsBox.hpp"
#include "SGE/debug/PointDebugShape.hpp"
#include "SGE/debug/LineDebugShape.hpp"
#include "PhysicsCircle.hpp"



std::string BoxSpawner::get_logic_type_id() {
    return "BoxSpawner";
}

void BoxSpawner::on_start() {
    LOG(10) << "on_start";

    auto dynamic_obj = scene()->spawn_gameobject("Dynamic Box ");
    dynamic_obj->logichub()->attach_logic(new PhysicsBox(1,1,true));

    auto dynamic_circle = scene()->spawn_gameobject("Dynamic Circle");
    dynamic_circle->transform()->set_local_position(10,10);
    dynamic_circle->logichub()->attach_logic(new PhysicsCircle());



    auto dynamic_obj2 = scene()->spawn_gameobject("Static Box ");
    dynamic_obj2->transform()->set_local_position(5,-10);
    dynamic_obj2->transform()->set_local_rotation(0.3);
    dynamic_obj2->logichub()->attach_logic(new PhysicsBox(20,1,false));

    auto dynamic_obj3 = scene()->spawn_gameobject("Static Box ");
    dynamic_obj3->transform()->set_local_position(-5,-5);
    dynamic_obj3->transform()->set_local_rotation(-0.3);
    dynamic_obj3->logichub()->attach_logic(new PhysicsBox(20,1,false));

    auto static_obj = scene()->spawn_gameobject("Static Box ");
    static_obj->transform()->set_local_position(0,-19);
    static_obj->logichub()->attach_logic(new PhysicsBox(1,10,false));





    // FIXME: the factory somehow doesn't complain with an inexistent id!!!

}

void BoxSpawner::on_update() {
    Logic::on_update();

}

