//
// Created by andrea on 5/21/19.
//
#include "TestLogic.hpp"
#include "SGE/components/graphics/VertArray.hpp"
#include "SGE/components/graphics/PathRenderer.hpp"
#include "SGE/debug/LineDebugShape.hpp"
#include "SGE/Path.hpp"

std::string TestLogic::get_logic_type_id() {
    return "TestLogic";
}

void TestLogic::on_start() {
    Logic::on_start();
    using namespace sge::cmp;
    using namespace sge;

    auto path_comp = gameobject()->add_component<PathRenderer>("PathRenderer");

    Path test_path;
    test_path.append_point(Vec2<float>(-500,0));
    test_path.append_point(Vec2<float>(-110,10));
    test_path.append_point(Vec2<float>(-300,0));
    test_path.append_point(Vec2<float>(200,600));

    Path load_path;
    load_path.load_from_file("../../resources/paths/randomized_circle.spath");

    path_comp->set_path(load_path);
    path_comp->set_color_all(sf::Color::White);
    path_comp->set_thickness(10);

    path_comp->set_closed(true);
}

void TestLogic::on_update() {

    //env()->doom_top_scene();


    Logic::on_update();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        increaser+= env()->delta_time()*0.3;
    gameobject()->transform()->set_local_rotation(increaser);
    auto res = sge::Vec2<float>(cosf(increaser)*400-600, sinf(increaser)*400);
    //gameobject()->get_component<sge::cmp::PathRenderer>("PathRenderer")->set_point(2,res);


    auto res2 = sge::Vec2<float>(cos(increaser)*300 + 100, -sin(increaser)*100 + 100);
    //gameobject()->get_component<sge::cmp::PathRenderer>("PathRenderer")->set_point(3,res2);

    //env()->debug_draw( new sge::debug::LineDebugShape(res.x,res.y,res2.x,res2.y));



}
