#include <SGE/components/physics/Rigidbody.hpp>
#include "PhysicsSandboxEntry.hpp"
#include "PhysicsPolygon.hpp"
#include "../old-test-logic/CameraControls.hpp"
#include "StaticPolygon.hpp"

std::string PhysicsSandboxEntry::get_logic_type_id() {
    return "PhysicsSandboxEntry";
}

void PhysicsSandboxEntry::on_start() {
    Logic::on_start();

    sge::Path path;
    path.append_point(sge::Vec2<float> (1, 1));
    path.append_point(sge::Vec2<float> (2, 1));
    path.append_point(sge::Vec2<float> (-1, 3));
    path.set_closed(true);
    auto bouncing_polygon = scene()->spawn_gameobject("Bouncing polygon");
    bouncing_polygon->logichub()->attach_logic(new PhysicsPolygon(path));

    sge::Path path1;
    path1.append_point(sge::Vec2<float> (-10, -4));
    path1.append_point(sge::Vec2<float> (10, -4));
    path1.append_point(sge::Vec2<float> (10, -5));
    path1.append_point(sge::Vec2<float> (-10, -5));
    path1.set_closed(true);
    auto static_wall = scene()->spawn_gameobject("Static wall 1");
    static_wall->transform()->set_local_position(10, 0);
    static_wall->logichub()->attach_logic(new StaticPolygon(path1));




    gameobject()->logichub()->attach_logic(new CameraControls(10, 1));

}
