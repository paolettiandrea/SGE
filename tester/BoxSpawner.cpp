#include "BoxSpawner.hpp"
#include "PhysicsBox.hpp"
#include "SGE/debug/PointDebugShape.hpp"
#include "SGE/debug/LineDebugShape.hpp"
#include "PhysicsCircle.hpp"
#include "Box.hpp"
#include "SGE/components/physics/ICollider.hpp"
#include "PhysicsPolygon.hpp"


std::string BoxSpawner::get_logic_type_id() {
    return "BoxSpawner";
}

void BoxSpawner::on_start() {
    LOG(10) << "on_start";


    cmp::Transform::visual_debug_general_switch = true;
    //cmp::PathRenderer::visual_debug_general_switch=true;
    cmp::ICollider::visual_debug_general_switch = true;


    auto polygon = scene()->spawn_gameobject("polygon");
    Path path;
    path.append_point(sge::Vec2<float>(-1,0));
    path.append_point(sge::Vec2<float>(-2,0));
    path.append_point(sge::Vec2<float>(-2,-3));
    path.append_point(sge::Vec2<float>(-2,-6));
    path.append_point(sge::Vec2<float>(-1,-6));
    path.append_point(sge::Vec2<float>(1, -3));
    path.set_closed(true);
    polygon->logichub()->attach_logic(new PhysicsPolygon(path));




    auto dynamic_obj = scene()->spawn_gameobject("Dynamic Box");
    dynamic_obj->transform()->set_local_position(10,0);
    dynamic_obj->transform()->set_local_rotation(M_PI/2);
    dynamic_obj->transform()->set_local_scale(2);
    dynamic_obj->logichub()->attach_logic(new PhysicsBox(2,2,true));




    auto dynamic_circle = scene()->spawn_gameobject("Dynamic Circle");
    dynamic_circle->transform()->set_local_position(1,1);
    dynamic_circle->transform()->set_local_scale(0.5);
    dynamic_circle->transform()->set_parent(dynamic_obj->transform());
    dynamic_circle->logichub()->attach_logic(new PhysicsCircle());

    auto dynamic_circle2 = scene()->spawn_gameobject("Dynamic Circle");
    dynamic_circle2->transform()->set_local_position(-1,1);
    dynamic_circle2->transform()->set_local_scale(0.9);
    dynamic_circle2->transform()->set_parent(dynamic_circle->transform());
    dynamic_circle2->logichub()->attach_logic(new PhysicsCircle());


    auto dynamic_obj2 = scene()->spawn_gameobject("Static Box");
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



/*
   parent_go = scene()->spawn_gameobject("Parent Box");
   parent_go->transform()->set_local_position(10.f,0);
   parent_go->logichub()->attach_logic(new Box(10,10));

   child_go = scene()->spawn_gameobject("Child Box");
   child_go->logichub()->attach_logic(new Box(3,3));
   child_go->transform()->set_local_position(5,5);
   child_go->transform()->set_parent(parent_go->transform());

    child_child_go = scene()->spawn_gameobject("Child Box");
    child_child_go->logichub()->attach_logic(new Box(1,1));
    child_child_go->transform()->set_local_position(2,2);
    child_child_go->transform()->set_parent(child_go->transform());

*/

    // FIXME: the factory somehow doesn't complain with an inexistent id!!!

}

void BoxSpawner::on_update() {
    Logic::on_update();

m_increaser += env()->fixed_delta_time();

}

