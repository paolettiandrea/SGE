//
// Created by andrea on 5/5/19.
//
#include "SGE/logic/Logic.hpp"
#ifndef FACTORY_EXPERIMENTS_HIERARCHYTESTLOGIC_HPP
#define FACTORY_EXPERIMENTS_HIERARCHYTESTLOGIC_HPP
class HierarchyTestLogic : public sge::Logic {
public:
    std::string get_logic_type_id() override {
        return "HierarchyTestLogic";
    }

    void on_start() override {
        auto go1 = scene()->spawn_gameobject("Child1");
        auto go2 = scene()->spawn_gameobject("Child2");
        auto go3 = scene()->spawn_gameobject("Child3");
        go1->transform()->set_parent(gameobject()->transform());
        go2->transform()->set_parent(gameobject()->transform());
        go3->transform()->set_parent(go2->transform());

        std::cout << gameobject()->get_string_local_hierarchy(true) << std::endl;
    }
};
#endif //FACTORY_EXPERIMENTS_HIERARCHYTESTLOGIC_HPP
