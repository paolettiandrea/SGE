#include "DebugShapesManager.hpp"

void sge::core::DebugShapesManager::add_debug_shape(sge::debug::DebugShape *new_shape) {
    new_shape->internal_initialization(debug_font);
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

void sge::core::DebugShapesManager::normalize_shapes_to_screen_size(float view_vertical_size) {
    if (m_last_vertical_size != view_vertical_size) {
        auto shape = debug_shapes_list.begin();
        for (; shape!=debug_shapes_list.end() ; ++shape) {
            (*shape)->update_dimensions(view_vertical_size);
        }
    }
}

sge::core::DebugShapesManager::~DebugShapesManager() {
    for (auto shape_p : debug_shapes_list) {
        delete(shape_p);
    }
}


