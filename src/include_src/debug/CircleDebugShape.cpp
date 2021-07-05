//
// Created by andrea on 6/16/19.
//

#include "SGE/debug/CircleDebugShape.hpp"

void sge::debug::CircleDebugShape::update_dimensions(float vertical_view_size) {
    center_point_debug_shape.update_dimensions(vertical_view_size);
}

void sge::debug::CircleDebugShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(center_point_debug_shape,states);
    target.draw(circle_vert_array, states);
}

void sge::debug::CircleDebugShape::internal_initialization(const sf::Font& debug_font) {
    DebugShape::internal_initialization(debug_font);
    center_point_debug_shape.internal_initialization(debug_font);
}
