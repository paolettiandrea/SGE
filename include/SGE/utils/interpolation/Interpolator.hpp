#ifndef PERLIN_TESTS_INTERPOLATOR_HPP
#define PERLIN_TESTS_INTERPOLATOR_HPP


#include <SFML/Graphics/Color.hpp>

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

class ColorInterpolator {
public:
    explicit ColorInterpolator(Interpolator *interpolator) {
        m_interpolator = interpolator;
    }

    virtual ~ColorInterpolator() {
        delete (m_interpolator);
    }

    sf::Color interpolate(float t, sf::Color starting_color, sf::Color ending_color) {
        sf::Color col;
        col.r = m_interpolator->interpolate(t, starting_color.r, ending_color.r);
        col.g = m_interpolator->interpolate(t, starting_color.g, ending_color.g);
        col.b = m_interpolator->interpolate(t, starting_color.b, ending_color.b);
        col.a = m_interpolator->interpolate(t, starting_color.a, ending_color.a);
        return col;
    }

private:
    Interpolator* m_interpolator;
};


#endif //PERLIN_TESTS_INTERPOLATOR_HPP
