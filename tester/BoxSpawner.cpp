#include "BoxSpawner.hpp"
#include "PhysicsBox.hpp"
#include "SGE/debug/PointDebugShape.hpp"
#include "SGE/debug/LineDebugShape.hpp"
#include "PhysicsCircle.hpp"
#include "Box.hpp"



std::string BoxSpawner::get_logic_type_id() {
    return "BoxSpawner";
}

void BoxSpawner::on_start() {
    LOG(10) << "on_start";
/*
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

*/


   parent_go = scene()->spawn_gameobject("Parent Box");
   parent_go->transform()->set_local_position(10.f,0);
   parent_go->logichub()->attach_logic(new Box(10,10));

   child_go = scene()->spawn_gameobject("Child Box");
   child_go->logichub()->attach_logic(new Box(3,3));
   child_go->transform()->set_local_position(5,5);
   child_go->transform()->set_parent(parent_go->transform());




    // FIXME: the factory somehow doesn't complain with an inexistent id!!!

}

void BoxSpawner::on_update() {
    Logic::on_update();

    m_increaser += env()->delta_time();
    auto yo = sinf(m_increaser);
    parent_go->transform()->set_local_scale(yo+1.1);
    parent_go->transform()->set_local_rotation(m_increaser);
    child_go->transform()->set_local_rotation(-m_increaser*5);

}

