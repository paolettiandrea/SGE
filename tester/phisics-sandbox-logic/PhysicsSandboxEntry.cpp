#include <SGE/components/physics/Rigidbody.hpp>
#include "PhysicsSandboxEntry.hpp"
#include "PhysicsPolygon.hpp"
#include "../old-test-logic/CameraControls.hpp"
#include "StaticPolygon.hpp"
#include "AnotherScript.hpp"

std::string PhysicsSandboxEntry::get_logic_type_id() {
    return "PhysicsSandboxEntry";
}

void PhysicsSandboxEntry::on_start() {
    Logic::on_start();

    sge::Path path1;
    path1.append_point(sge::Vec2<float> (-10, -1));
    path1.append_point(sge::Vec2<float> (10, -1));
    path1.append_point(sge::Vec2<float> (10, 1));
    path1.append_point(sge::Vec2<float> (-10, 1));
    path1.set_closed(true);
    static_wall = scene()->spawn_gameobject("Static wall 1");
    static_wall->transform()->set_local_position(5, -10);
    static_wall->transform()->set_local_rotation(M_PI_2/4);
    static_wall->logichub()->attach_logic(new StaticPolygon(path1));
    rb = static_wall->get_component<sge::cmp::Rigidbody>("Rigidbody");
    rb->set_body_type(b2_kinematicBody);


    auto static_wall2 = scene()->spawn_gameobject("Static wall 2");
    static_wall2->transform()->set_local_position(-5, -10);
    static_wall2->transform()->set_local_rotation(-M_PI_2/4);
    static_wall2->logichub()->attach_logic(new StaticPolygon(path1));



    /*auto go = scene()->spawn_gameobject("Camera manager");
    go->logichub()->attach_logic(new CameraControls(10, 1));
    go->logichub()->attach_logic(new AnotherScript());
    go->logichub()->attach_logic(new AnotherScript());

     */

    gameobject()->logichub()->attach_logic(new AnotherScript());
    gameobject()->logichub()->attach_logic(new CameraControls(10,5));

    for (int i = 0; i < 6; ++i) {
        spawn_bouncer("Initial bouncer " + std::to_string(i));
    }

}

void PhysicsSandboxEntry::on_fixed_update() {
    Logic::on_fixed_update();
    auto pos = static_wall->transform()->get_local_position();
    static_wall->transform()->set_local_position(pos.x, pos.y+0.01);
}

void PhysicsSandboxEntry::on_update() {
    Logic::on_update();

    accumulator += env()->delta_time();

    if (accumulator>1){
        accumulator -= 1;
        for (int i = 0; i < 3; ++i) {

            spawn_bouncer("Bouncer " + std::to_string(bouncer_counter));
            bouncer_counter++;
        }
    }
}

void PhysicsSandboxEntry::spawn_bouncer(const std::string& name) {
    sge::Path path;
    path.append_point(sge::Vec2<float> (1, 1));
    path.append_point(sge::Vec2<float> (2, 1));
    path.append_point(sge::Vec2<float> (-1, 3));
    path.set_closed(true);
    auto bouncing_polygon = scene()->spawn_gameobject(name);
    bouncing_polygon->logichub()->attach_logic(new PhysicsPolygon(path));
}
