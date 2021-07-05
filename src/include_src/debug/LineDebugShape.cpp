//
// Created by andrea on 5/16/19.
//

#include <cmath>
#include <iostream>
#include "SGE/debug/LineDebugShape.hpp"




sge::debug::LineDebugShape::LineDebugShape(float x1, float y1, float x2, float y2, float duration,
                                           unsigned int coord_decimals,
                                           const std::string &label, sf::Color color)
                                           : DebugShape(duration)
                                           , m_point1_debug_shape(x1,y1,duration, label, coord_decimals,color)
                                           , m_point2_debug_shape(x2,y2,duration, "", coord_decimals,color)
                                           , line_rect(sf::Vector2f(1.f,1.f)){
    line_vertarray.setPrimitiveType(sf::PrimitiveType::Lines);
    line_vertarray.append(sf::Vertex(sf::Vector2f(x1,-y1)));
    line_vertarray.append(sf::Vertex(sf::Vector2f(x2,-y2)));
    line_vertarray[0].color=color;
    line_vertarray[1].color=color;

}

void sge::debug::LineDebugShape::update_dimensions(float vertical_view_size) {
    m_point1_debug_shape.update_dimensions(vertical_view_size);
    m_point2_debug_shape.update_dimensions(vertical_view_size);
}

void sge::debug::LineDebugShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(line_vertarray, states);
    target.draw(m_point1_debug_shape, states);
    target.draw(m_point2_debug_shape, states);

}

void sge::debug::LineDebugShape::internal_initialization(const sf::Font &debug_font) {
    DebugShape::internal_initialization(debug_font);
    m_point1_debug_shape.internal_initialization(debug_font);
    m_point2_debug_shape.internal_initialization(debug_font);
}

