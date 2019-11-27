#ifndef PERLIN_TESTS_INTERPOLATOR_HPP
#define PERLIN_TESTS_INTERPOLATOR_HPP


class Interpolator {
public:
    virtual ~Interpolator();

    virtual float interpolate(float t, float a, float b) = 0;

    static float clamp(float x, float lowerlimit, float upperlimit) {
        if (x < lowerlimit)
            x = lowerlimit;
        if (x > upperlimit)
            x = upperlimit;
        return x;
    }
};


class LinearInterpolator : public  Interpolator {
public:
    float interpolate(float t, float a, float b) override;
};

class RootInterpolator : public Interpolator {
public:
    RootInterpolator (float factor, bool inverted=false) : m_inverted(inverted), m_factor(factor) {}

    float interpolate(float t, float a, float b) override;

private:
    float m_factor;
    bool m_inverted;
};

class SmoothInterpolator : public Interpolator {
public:
    SmoothInterpolator() {}

    float interpolate(float t, float a, float b) override {
        // Scale, bias and saturate x to 0..1 range
        float x = Interpolator::clamp((t - a) / (b - a), 0.0, 1.0);
        // Evaluate polynomial
        return x * x * (3 - 2 * x);


    }
};


#endif //PERLIN_TESTS_INTERPOLATOR_HPP
