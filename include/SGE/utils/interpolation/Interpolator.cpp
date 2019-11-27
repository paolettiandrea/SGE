#include "Interpolator.hpp"
#include <cmath>

Interpolator::~Interpolator() {

}

float LinearInterpolator::interpolate(float t, float a, float b) {
    return (b-a)*t + a;
}

float RootInterpolator::interpolate(float t, float a, float b) {
    if (m_inverted) t = 1-t;
    return (b-a)*powf(t,1.f/m_factor) + a;
}
