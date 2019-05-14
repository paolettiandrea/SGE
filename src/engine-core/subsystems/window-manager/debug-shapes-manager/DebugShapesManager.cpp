//
// Created by andrea on 5/14/19.
//

#include "DebugShapesManager.hpp"

void sge::core::DebugShapesManager::add_debug_shape(sge::debug::DebugShape *new_shape) {
    debug_shapes_list.push_back(new_shape);
}

void sge::core::DebugShapesManager::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    auto shape = debug_shapes_list.begin();
    for (; shape!=debug_shapes_list.end() ; ++shape) {
        target.draw(**shape, states);
    }
}

void sge::core::DebugShapesManager::remove_expired_shapes() {
    debug_shapes_list.remove_if(is_discardable_check_and_delete);
}

bool sge::core::DebugShapesManager::is_discardable_check_and_delete(debug::DebugShape *shape) {
    if (shape->is_discardable()) {      // Pretty bad design,
        delete(shape);
        return true;
    } else {
        return false;
    }
}
