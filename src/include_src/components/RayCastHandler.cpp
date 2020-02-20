#include <Box2D/Dynamics/b2Fixture.h>
#include "SGE/components/physics/RayCastHandler.hpp"
#include <SGE//components//physics//Collider.hpp>
#include <SGE/GameObject.hpp>
#include <SGE/Scene.hpp>

float32 sge::RayCastHandler::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) {
    auto col = (sge::cmp::Collider*)fixture->GetUserData();
    if (!col->is_sensor()) {
        if (col->get_rigidbody() != ignore_rb && filter.maskBits & fixture->GetFilterData().categoryBits) {
            if (fraction > SGE_RAYCAST_FRACTION_IGNORE_DELTA) {
                output.point = sge::Vec2<float>(point.x, point.y);
                output.normal = sge::Vec2<float>(normal.x, normal.y);
                output.fraction = fraction;
                //std::cout << fraction << std::endl;
                //col->gameobject()->get_scene()->env()->debug_draw_point(output.point, 5, "yes", 0, sf::Color::Green);
                return fraction;
            }
        }
    }

    //std::cout << "Ignored\n";
    //col->gameobject()->get_scene()->env()->debug_draw_point(sge::Vec2<float>(point.x, point.y), 5, "", 0, sf::Color::Blue);

    return -1;

}

sge::RayCastHandler::RayCastHandler(b2Filter filter1, Rigidbody_H ignore_rb , sge::Vec2<float> point_a, sge::Vec2<float> point_b) {
    this->filter = filter1;
    this->ignore_rb = ignore_rb;
    this->point_a = point_a;
    this->point_b = point_b;
    output.point = point_b;
    output.fraction = 1;
}

const sge::Vec2<float> &sge::RayCastHandler::get_point_a() const {
    return point_a;
}

const sge::Vec2<float> &sge::RayCastHandler::get_point_b() const {
    return point_b;
}

void sge::RayCastHandler::prepare_for_raycast() {
    output.point = point_b;
}
