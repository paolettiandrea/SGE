#include <iostream>
#include <iomanip>
#include "FpsCounter.hpp"

void sge::core::debug::FpsCounter::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(text);
}

void sge::core::debug::FpsCounter:: count_frame() {
    std::chrono::duration<float,std::milli> delta_time = std::chrono::steady_clock::now() - last_flush_tp;
    if (delta_time.count()/1000.0 >= SGE_DEBUG_FPS_COUNTER_REFRESH_PERIOD) {
        // Time to do a new flush, consider the period from the last flush to the last count
        std::chrono::duration<float,std::milli> actual_delta = last_count_tp - last_flush_tp;
        auto actual_delta_count = actual_delta.count()/1000.0;
        auto fps = (float)frame_counter / actual_delta_count;
        std::stringstream stream;
        stream << std::fixed << std::setprecision(1) << fps;
        text.setString(stream.str());

        frame_counter = 1;
        last_flush_tp = last_count_tp;

    } else {
        frame_counter++;
    }
    last_count_tp = std::chrono::steady_clock::now();
}
