#include "SGE/debug/PointDebugShape.hpp"


sge::debug::PointDebugShape::PointDebugShape(float x, float y, float duration)
: DebugShape(duration)
, m_dot_shape(500.f) {
    m_dot_shape.setOrigin(500,500);
    m_dot_shape.setPosition(x,y);
    m_dot_shape.setFillColor(sf::Color::White);
}

void sge::debug::PointDebugShape::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(m_dot_shape, states);
}
