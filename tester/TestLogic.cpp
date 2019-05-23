//
// Created by andrea on 5/21/19.
//
#include "TestLogic.hpp"
#include "SGE/components/graphics/VertArray.hpp"


std::string TestLogic::get_logic_type_id() {
    return "TestLogic";
}

void TestLogic::on_start() {
    Logic::on_start();
    using namespace sge::cmp;

    auto vert_array_comp = gameobject()->add_component<VertArray>("VertArray");
    vert_array_comp->set_primitive(sf::PrimitiveType::Triangles);
    vert_array_comp->set_color(sf::Color::White);
    vert_array_comp->append_local_point(sge::Vec2<float>(0,0));
    vert_array_comp->append_local_point(sge::Vec2<float>(-10,40));
    vert_array_comp->append_local_point(sge::Vec2<float>(-10,-40));
    std::cout << gameobject()->get_string_local_hierarchy(true) << std::endl;
}

void TestLogic::on_update() {
    Logic::on_update();
    increaser+= env()->delta_time();
    gameobject()->transform()->set_local_position(gameobject()->transform()->get_local_position().x + env()->delta_time()*100, 0);
    gameobject()->transform()->set_local_scale(gameobject()->transform()->get_local_scale().x+env()->delta_time()*1);
    gameobject()->transform()->set_local_rotation(increaser);

    //gameobject()->transform()->set_local_rotation(gameobject()->transform()->get_local_rotation()+env()->delta_time()*1);
    LOG_INFO << "Rotation: " << gameobject()->transform()->get_local_rotation_euler();
    // FIXME: get_local_rotation doesn't work properly (probably also world), probably due to the way we retrieve the rotation
}
