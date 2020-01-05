#include "Animation.hpp"

sge::Animation::Animation(Interpolator *interpolator, float from_val, float to_val, float duration) {
    m_duration = duration;
    m_interpolator = interpolator;
    m_from_val = from_val;
    m_to_val = to_val;
}

float sge::Animation::get_fraction() {
    return m_elapsed_seconds/m_duration;
}

void sge::Animation::start(bool reset) {
    m_active = true;

    if (reset) {
        m_elapsed_seconds = 0;
    }
}

void sge::Animation::stop() {
    m_active = false;
}

sge::Animation::~Animation() {
    delete (m_interpolator);
}

float sge::Animation::step(float delta_time) {

    if (m_active) {
        m_elapsed_seconds += delta_time;
        if (m_elapsed_seconds>m_duration) {
            on_animation_ended();
            m_active = false;
            return m_to_val;
        }
    }
    return get_val();
}

void sge::Animation::set_duration(float seconds) {
    m_duration = seconds;
}

void sge::Animation::set_to_val(float val) {
    m_to_val = val;
}

void sge::Animation::set_from_val(float val) {
    m_from_val = val;
}

float sge::Animation::get_val() {
    return m_interpolator->interpolate(m_elapsed_seconds/m_duration, m_from_val, m_to_val);
}

bool sge::Animation::is_done() {
    return !m_active;
}

bool sge::Animation::is_active() {
    return m_active;
}

