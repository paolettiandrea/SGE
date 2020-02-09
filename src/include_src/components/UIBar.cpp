#include <iostream>
#include "SGE/components/graphics/ui/blocks/UIBar.hpp"

void sge::UIBar::set_position(sf::Vector2f position) {
    m_position = position;
    dirty_geometry = true;
}

void sge::UIBar::set_origin(sf::Vector2f origin) {
    m_origin = origin;
    dirty_geometry = true;
}

sf::FloatRect sge::UIBar::get_bounds() {
    return sf::FloatRect(0,0, width, height);
}

sge::UIBar::UIBar(float width, float height) : height(height), width(width) {

    bar_rectangle.setPrimitiveType(sf::PrimitiveType::Quads);
    bar_rectangle.append(m_origin);
    bar_rectangle.append(m_origin);
    bar_rectangle.append(m_origin);
    bar_rectangle.append(m_origin);

    set_bar_color(sf::Color::White);

    background_rectangle.setPrimitiveType(sf::PrimitiveType::Quads);
    background_rectangle.append(m_origin);
    background_rectangle.append(m_origin);
    background_rectangle.append(m_origin);
    background_rectangle.append(m_origin);

    set_background_color(sf::Color(100, 100, 100, 100));
}

void sge::UIBar::set_bar(float filled_factor) {

    m_filled_factor =filled_factor;
    dirty_geometry = true;
#if DEBUG
    if (0 > filled_factor || filled_factor > 1) {
        std::cerr << "UIBar received a factor ouside of range [0,1]: " << filled_factor << std::endl;
    }
#endif


}

void sge::UIBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(background_rectangle, states);
    target.draw(bar_rectangle, states);
}

void sge::UIBar::prepare_for_draw() {
    if (dirty_geometry) {
        clean_geometry();
    }
}

void sge::UIBar::clean_geometry() {
    bar_rectangle[0].position = -m_origin + m_position;
    bar_rectangle[1].position = -m_origin + sf::Vector2f(0, height) + m_position;
    bar_rectangle[2].position = -m_origin + sf::Vector2f(width*m_filled_factor, height) + m_position;
    bar_rectangle[3].position = -m_origin + sf::Vector2f(width*m_filled_factor, 0) + m_position;

    background_rectangle[0].position = -m_origin + m_position;
    background_rectangle[1].position = -m_origin + sf::Vector2f(0, height) + m_position;
    background_rectangle[2].position = -m_origin + sf::Vector2f(width, height) + m_position;
    background_rectangle[3].position = -m_origin + sf::Vector2f(width, 0) + m_position;

    dirty_geometry = false;
}

void sge::UIBar::set_background_color(sf::Color color) {
    for (int j = 0; j < background_rectangle.getVertexCount(); ++j) {
        background_rectangle[j].color = color;
    }
}

void sge::UIBar::set_bar_color(sf::Color color) {
    for (int i = 0; i < bar_rectangle.getVertexCount(); ++i) {
        bar_rectangle[i].color = color;
    }
}

void sge::UIBar::set_size(float width, float height) {
    this->width = width;
    this->height = height;
    dirty_geometry = true;
    make_bounds_dirty();
}
