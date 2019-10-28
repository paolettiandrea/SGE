#include <SGE/Vec2.hpp>
#include "Camera.hpp"

sge::Camera::Camera(float vertical_size)
    : m_view(sf::Vector2f(0.f,0.f), sf::Vector2f(1.f,1.f))
    {
    m_screen_ratio = -1;
    m_vertical_size = vertical_size;
    update_view_size();
}

void sge::Camera::set_zoom(float vertical_size) {
    m_vertical_size = vertical_size;
    update_view_size();
    changed_view_flag = true;
}

void sge::Camera::set_ratio(float screen_ratio) {
    m_screen_ratio = screen_ratio;
    update_view_size();
    changed_view_flag = true;
}


void sge::Camera::offset_zoom(float vertical_size_offset) {
    m_vertical_size += vertical_size_offset;
    update_view_size();
    changed_view_flag = true;
}

const sf::View &sge::Camera::get_view() const {
    return m_view;
}

void sge::Camera::update_view_size() {
    m_view.setSize(m_vertical_size*m_screen_ratio, m_vertical_size);
    changed_view_flag=true;
}

void sge::Camera::set_center(float x, float y) {
    m_view.setCenter(x,-y);
    changed_view_flag = true;
}

void sge::Camera::offset_center(float x_offset, float y_offset) {
    set_center(m_view.getCenter().x + x_offset, m_view.getCenter().y + y_offset);
}

float sge::Camera::get_zoom() {
    return m_vertical_size;
}

void sge::Camera::set_center(const sge::Vec2<float>& point) {
    set_center(point.x, point.y);
}


