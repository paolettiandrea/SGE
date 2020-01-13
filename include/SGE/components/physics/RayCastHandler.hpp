#ifndef NON_GRAVITAR_RAYCASTHANDLER_HPP
#define NON_GRAVITAR_RAYCASTHANDLER_HPP


#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <SGE/Vec2.hpp>
#include "Rigidbody.hpp"

namespace sge {

    struct RayCastOutput {
        sge::Vec2<float> point;
        sge::Vec2<float> normal;
        float fraction;
    };

    class RayCastHandler : public b2RayCastCallback {
    public:
        RayCastHandler(b2Filter filter1, Rigidbody_H ignore_rb);
        float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) override;

        sge::Vec2<float> point_a, point_b;

        RayCastOutput get_output() { return output; }

    private:
        b2Filter filter;
        RayCastOutput output;
        Rigidbody_H ignore_rb;
    };
}



#endif //NON_GRAVITAR_RAYCASTHANDLER_HPP
