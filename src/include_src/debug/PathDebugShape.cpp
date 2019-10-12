//
// Created by andrea on 6/16/19.
//

#include "SGE/debug/PathDebugShape.hpp"


void sge::debug::PathDebugShape::update_dimensions(float vertical_view_size) {
    for (int i = 0; i < point_debug_shapes.size(); ++i) {
        point_debug_shapes[i].update_dimensions(vertical_view_size);
    }
}

void sge::debug::PathDebugShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for (int i = 0; i < point_debug_shapes.size(); ++i) {
        target.draw(point_debug_shapes[i],states);
    }
    target.draw(lines_vert_array, states);
}

void sge::debug::PathDebugShape::internal_initialization(const sf::Font& debug_font) {
    DebugShape::internal_initialization(debug_font);
    for (int i = 0; i < point_debug_shapes.size(); ++i) {
        point_debug_shapes[i].internal_initialization(debug_font);
    }
}
