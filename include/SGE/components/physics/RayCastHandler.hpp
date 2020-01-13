#ifndef NON_GRAVITAR_RAYCASTHANDLER_HPP
#define NON_GRAVITAR_RAYCASTHANDLER_HPP


#include <Box2D/Dynamics/b2WorldCallbacks.h>
#include <SGE/Vec2.hpp>
#include "Rigidbody.hpp"

#define SGE_RAYCAST_FRACTION_IGNORE_DELTA 1.0e-05

namespace sge {

    struct RayCastOutput {
        sge::Vec2<float> point;
        sge::Vec2<float> normal;
        float fraction;
    };

    class Scene;
    class RayCastHandler : public b2RayCastCallback {
        friend class Scene;
    public:
        RayCastHandler(b2Filter filter1, Rigidbody_H ignore_rb, sge::Vec2<float> point_a, sge::Vec2<float> point_b);
        float32 ReportFixture(b2Fixture *fixture, const b2Vec2 &point, const b2Vec2 &normal, float32 fraction) override;

        RayCastOutput get_output() { return output; }

    private:

        sge::Vec2<float> point_a, point_b;
    public:
        const Vec2<float> &get_point_a() const;

        const Vec2<float> &get_point_b() const;

    protected:
        virtual void prepare_for_raycast();
    private:
        b2Filter filter;
        RayCastOutput output;
        Rigidbody_H ignore_rb;
    };
}



#endif //NON_GRAVITAR_RAYCASTHANDLER_HPP
