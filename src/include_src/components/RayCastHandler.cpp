#include <Box2D/Dynamics/b2Fixture.h>
#include "SGE/components/physics/RayCastHandler.hpp"
#include <SGE//components//physics//Collider.hpp>
#include <SGE/GameObject.hpp>
#include <SGE/Scene.hpp>

float32 sge::RayCastHandler::ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) {
    auto col = (sge::cmp::Collider*)fixture->GetUserData();
    if (col->get_filter_data().categoryBits & filter.maskBits && !col->is_sensor()) {
        if (col->get_rigidbody() != ignore_rb) {
            output.point = sge::Vec2<float>(point.x, point.y);
            output.normal = sge::Vec2<float>(normal.x, normal.y);
            output.fraction = fraction;
            return 0;
        }
    }

    std::cout << "Ignored\n";
    output.point = sge::Vec2<float>(point.x, point.y);
    col->gameobject()->get_scene()->env()->debug_draw_point(output.point, 5, "", 0, sf::Color::Blue);

    return -1;

}

sge::RayCastHandler::RayCastHandler(b2Filter filter1, Rigidbody_H ignore_rb) {
    this->filter = filter1;
    this->ignore_rb = ignore_rb;
}
