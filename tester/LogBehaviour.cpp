//
// Created by andrea on 4/30/19.
//

#include "LogBehaviour.hpp"
#include "TestTransform.hpp"
#include <cmath>

std::string LogBehaviour::get_logic_type_id() {
    return "LogBehaviour";
}

void LogBehaviour::on_start() {
    LOG(10) << "on_start";
    env()->doom_top_scene();
    TestTransform test_transform;
    test_transform.set_translation(0,0);
    test_transform.set_rotation(M_PI/2);
    auto res = test_transform.transform_point(sge::Vec2<float>(2,4));
    std::cout << "Result: " << res.to_string() << std::endl;

}

void LogBehaviour::on_destruction() {
    LOG(10) << "on_destruction";
}

void LogBehaviour::on_update() {
    LOG_DEBUG(10) << "on_update";
}

void LogBehaviour::on_fixed_update() {
    LOG_DEBUG(10) << "on_fixed_update";
}
