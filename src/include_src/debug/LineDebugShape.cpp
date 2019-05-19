//
// Created by andrea on 5/16/19.
//

#include <cmath>
#include "SGE/debug/LineDebugShape.hpp"

#ifndef LINE_DEBUG_SHAPE_THICKNESS_SCREEN_RATIO
#define LINE_DEBUG_SHAPE_THICKNESS_SCREEN_RATIO 0.002
#endif




sge::debug::LineDebugShape::LineDebugShape(float x1, float y1, float x2, float y2, float duration,
                                           unsigned int coord_decimals)
                                           : DebugShape(duration)
                                           , m_point1_debug_shape(x1,y1,duration, "", coord_decimals)
                                           , m_point2_debug_shape(x2,y2,duration, "", coord_decimals)
                                           , line_rect(sf::Vector2f(1.f,1.f)){
    line_rect.setFillColor(DebugShape::primary_debug_color);
    line_rect.setOrigin(sf::Vector2f(0.5f, 1.f));
    line_rect.setPosition(x1,y1);
    float ipotenusa = std::sqrt(pow(x1-x2, 2) + pow(y1-y2, 2));
    double proj = (y1-y2)/ipotenusa;
    float angle = asin(proj)*180/M_PI - 90;
    line_rect.setRotation(angle);
    line_rect.setScale(sf::Vector2f(1.f,ipotenusa));
}

void sge::debug::LineDebugShape::update_dimensions(float vertical_view_size) {
    m_point1_debug_shape.update_dimensions(vertical_view_size);
    m_point2_debug_shape.update_dimensions(vertical_view_size);
    line_rect.setScale(sf::Vector2f(LINE_DEBUG_SHAPE_THICKNESS_SCREEN_RATIO*vertical_view_size, line_rect.getScale().y));

}

void sge::debug::LineDebugShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(line_rect, states);
    target.draw(m_point1_debug_shape, states);
    target.draw(m_point2_debug_shape, states);

}

void sge::debug::LineDebugShape::internal_initialization(const sf::Font &debug_font) {
    DebugShape::internal_initialization(debug_font);
    m_point1_debug_shape.internal_initialization(debug_font);
    m_point2_debug_shape.internal_initialization(debug_font);
}

