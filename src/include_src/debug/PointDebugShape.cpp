#include "SGE/debug/PointDebugShape.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

#ifndef POINT_DEBUG_SHAPE_DOT_SCREEN_RATIO
#define POINT_DEBUG_SHAPE_DOT_SCREEN_RATIO 0.003
#endif
#ifndef POINT_DEBUG_SHAPE_OUTLINE_SCREEN_RATIO
#define POINT_DEBUG_SHAPE_OUTLINE_SCREEN_RATIO 0.003
#endif
#ifndef POINT_DEBUG_SHAPE_TEXT_OUTLINE_SCREEN_RATIO
#define POINT_DEBUG_SHAPE_TEXT_OUTLINE_SCREEN_RATIO 0.002
#endif

sge::debug::PointDebugShape::PointDebugShape(float x, float y, float duration, const std::string& label, unsigned int coords_digits)
: DebugShape(duration) {
    m_dot_shape.setPosition(x,y);
    m_dot_shape.setFillColor(sf::Color::Black);
    m_dot_shape.setOutlineColor(DebugShape::primary_debug_color);

    if (coords_digits>0 || label!="") {
        m_coordinates_text.setFont(debug_font);
        m_coordinates_text.setFillColor(DebugShape::primary_debug_color);
        m_coordinates_text.setCharacterSize(27);
        m_coordinates_text.setPosition(x,y);
        std::stringstream ss;
        if (coords_digits>0) ss << std::fixed << "(" << std::setprecision(coords_digits) << x << ", " << y << ")\n";
        ss << label;
        m_coordinates_text.setString(ss.str());
        m_coordinates_text.setOrigin(0,0);
        sf::Color col(sf::Color::Black);
        col.a = 200;
        m_coordinates_text.setOutlineColor(col);
        m_coordinates_text.setOutlineThickness(2);
    }

}

void sge::debug::PointDebugShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_dot_shape, states);
    auto yo = m_coordinates_text.getString();
    target.draw(m_coordinates_text, states);
}

void sge::debug::PointDebugShape::update_dimensions(float new_vertical_screen_size) {
    float normalized_radius = new_vertical_screen_size*POINT_DEBUG_SHAPE_DOT_SCREEN_RATIO/2;
    float normalized_thickness = new_vertical_screen_size*POINT_DEBUG_SHAPE_OUTLINE_SCREEN_RATIO;
    m_dot_shape.setOrigin(normalized_radius, normalized_radius);
    m_dot_shape.setRadius(normalized_radius);
    m_dot_shape.setOutlineThickness(normalized_thickness);
    m_coordinates_text.setScale(new_vertical_screen_size*0.0011, new_vertical_screen_size*0.0011);
}
