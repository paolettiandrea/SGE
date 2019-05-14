//
// Created by andrea on 5/2/19.
//

#ifndef FACTORY_EXPERIMENTS_WIGGLER_HPP
#define FACTORY_EXPERIMENTS_WIGGLER_HPP

#include "SGE/logic/Logic.hpp"
#include "SGE/components/Polygon.hpp"
#include <math.h>

using namespace sge;

class Wiggler : public sge::Logic {
public:
    explicit Wiggler(double speed, Vec2<double> center, double radius) : m_speed(speed), m_center(center), m_radius(radius) {}

    std::string get_logic_type_id() override {
        return "Wiggler";
    }

    void on_start() override {
        LOG_DEBUG(30) << "on_start";
        //env()->book_new_scene_push("Recursive scene " + std::to_string(depth+1), new Wiggler(depth+1));
        auto poly = gameobject()->add_component<cmp::Polygon>("Polygon");
        poly->set_polygon(10.f, 9);
    }

    void on_update() override {
        Logic::on_update();
        m_angle += m_speed*env()->delta_time();
        gameobject()->transform()->set_local_position(m_center.x+(sin(m_angle))*m_radius,
                                                      m_center.y+(cos(m_angle))*m_radius);
    }

private:
    double m_speed;
    double m_angle = 0;
    Vec2<double> m_center;
    double m_radius;

};
#endif //FACTORY_EXPERIMENTS_WIGGLER_HPP
