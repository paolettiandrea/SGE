#include "SGE/debug/PointDebugShape.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

#ifndef POIINT_DEBUG_CROSS_RATIO
#define POIINT_DEBUG_CROSS_RATIO 0.005
#endif
#ifndef POINT_DEBUG_SHAPE_OUTLINE_SCREEN_RATIO
#define POINT_DEBUG_SHAPE_OUTLINE_SCREEN_RATIO 0.003
#endif
#ifndef POINT_DEBUG_SHAPE_TEXT_OUTLINE_SCREEN_RATIO
#define POINT_DEBUG_SHAPE_TEXT_OUTLINE_SCREEN_RATIO 0.002
#endif

sge::debug::PointDebugShape::PointDebugShape(float x, float y, float duration, const std::string& label, unsigned int coords_digits, sf::Color color)
: DebugShape(duration)
, pos_vec(x, -y) {

    if (coords_digits>0 || label!="") {
        m_coordinates_text.setFont(debug_font);
        m_coordinates_text.setFillColor(color);
        m_coordinates_text.setCharacterSize(27);
        m_coordinates_text.setPosition(x,-y);
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

    cross_vertarray.setPrimitiveType(sf::PrimitiveType::Lines);
    cross_vertarray.append(sf::Vertex(sf::Vector2f(0,0), color));
    cross_vertarray.append(sf::Vertex(sf::Vector2f(0,0), color));
    cross_vertarray.append(sf::Vertex(sf::Vector2f(0,0), color));
    cross_vertarray.append(sf::Vertex(sf::Vector2f(0,0), color));


}

void sge::debug::PointDebugShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    //target.draw(m_dot_shape, states);
    auto yo = m_coordinates_text.getString();
    target.draw(m_coordinates_text, states);
    target.draw(cross_vertarray, states);
}

void sge::debug::PointDebugShape::update_dimensions(float new_vertical_screen_size) {
    m_coordinates_text.setScale(new_vertical_screen_size*0.0011, new_vertical_screen_size*0.0011);

    cross_vertarray[0].position = sf::Vector2f(pos_vec.x, pos_vec.y+new_vertical_screen_size*POIINT_DEBUG_CROSS_RATIO);
    cross_vertarray[1].position = sf::Vector2f(pos_vec.x, pos_vec.y-new_vertical_screen_size*POIINT_DEBUG_CROSS_RATIO);
    cross_vertarray[2].position = sf::Vector2f(pos_vec.x+new_vertical_screen_size*POIINT_DEBUG_CROSS_RATIO, pos_vec.y);
    cross_vertarray[3].position = sf::Vector2f(pos_vec.x-new_vertical_screen_size*POIINT_DEBUG_CROSS_RATIO, pos_vec.y);
}
