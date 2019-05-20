//
// Created by andrea on 5/5/19.
//
#include "SGE/logic/Logic.hpp"
#include "SGE/debug/LineDebugShape.hpp"
#ifndef FACTORY_EXPERIMENTS_HIERARCHYTESTLOGIC_HPP
#define FACTORY_EXPERIMENTS_HIERARCHYTESTLOGIC_HPP

class HierarchyTestLogic : public sge::Logic {
public:
    std::string get_logic_type_id() override {
        return "HierarchyTestLogic";
    }

    void on_start() override {
        //env()->doom_top_scene();
        gameobject()->transform()->set_local_position(0,0);
        gameobject()->transform()->set_local_scale(2);
        gameobject()->transform()->set_local_rotation(M_PI/2);
        auto child = scene()->spawn_gameobject("Child1");
        child->transform()->set_local_position(0,0);
        child->transform()->set_local_rotation(M_PI/2);
        child->transform()->set_local_scale(2);
        child->transform()->set_parent(gameobject()->transform());
        std::cout << child->transform()->get_world_position().to_string() << std::endl;

        std::cout << gameobject()->get_string_local_hierarchy(true) << std::endl;
        Vec2<double> a(10,10);
        Vec2<double> b(100,100);

        auto res_a = child->transform()->local_to_world_point(a);
        auto res_b = child->transform()->local_to_world_point(b);
        env()->debug_draw(new debug::LineDebugShape(a.x,a.y,b.x,b.y,10,1, "original"));
        env()->debug_draw(new debug::LineDebugShape(res_a.x,res_a.y,res_b.x,res_b.y,10,1, "result"));

        std::cout << std::to_string(child->transform()->get_world_rotation_euler()) << std::endl;
    }
};
#endif //FACTORY_EXPERIMENTS_HIERARCHYTESTLOGIC_HPP
