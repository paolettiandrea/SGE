//
// Created by andrea on 5/14/19.
//

#include "SGE/debug/DebugShape.hpp"

sf::Color sge::debug::DebugShape::default_debug_color(255,117,26);

sge::debug::DebugShape::DebugShape(float duration) {
    using namespace std::chrono;
    discard_time_point = steady_clock::now() + microseconds(int(duration*1000000));
}

bool sge::debug::DebugShape::is_discardable() {
    using namespace std::chrono;
    return steady_clock::now() > discard_time_point;
}

void sge::debug::DebugShape::internal_initialization(const sf::Font& font) {
    debug_font = font;
}


