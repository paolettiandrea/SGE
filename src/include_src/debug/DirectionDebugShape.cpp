//
// Created by andrea on 6/16/19.
//

#include "SGE/debug/DirectionDebugShape.hpp"

void sge::debug::DirectionDebugShape::update_dimensions(float vertical_view_size) {

}

void sge::debug::DirectionDebugShape::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(arrow_vert_array,states);
}
