#include <iostream>
#include "Profiler.hpp"


void sge::core::debug::Profiler::start(const std::string &id) {
    if (starting_time_map.count(id)==0) {
        starting_time_map[id] = std::chrono::steady_clock::now();
    } else {
        std::cerr << id << " was already started" << std::endl;
        exit(1);
    }
}

void sge::core::debug::Profiler::stop(const std::string &id) {
    if (starting_time_map.count(id) > 0) {
        auto delta = std::chrono::steady_clock::now() - starting_time_map[id];
        float delta_microseconds = std::chrono::duration_cast<std::chrono::microseconds>(delta).count();

        if (buffer_map.count(id)>0) buffer_map[id] += delta_microseconds;
        else buffer_map[id] = delta_microseconds;

        starting_time_map.erase(id);
    } else {
        std::cerr << id << " was not started" << std::endl;
    }
}

void sge::core::debug::Profiler::increase_dump_counter() {
    m_dump_counter++;

    if (m_dump_counter >= SGE_DEBUG_PROFILER_SAMPLE_FRAMES_NUMBER) {
        auto delta = std::chrono::steady_clock::now() - last_dump_time;
        total_dump_time = std::chrono::duration_cast<std::chrono::microseconds>(delta).count();

        dump_map.clear();
        for (auto pair : buffer_map) {
            if (dump_map[pair.first]>0) dump_map[pair.first] += pair.second;
            else dump_map[pair.first] = pair.second;
        }
        buffer_map.clear();

        last_dump_time = std::chrono::steady_clock::now();

        m_dump_counter = 0;
    }



}

std::vector<std::pair<std::string, int>> sge::core::debug::Profiler::get_count() {
    std::vector<std::pair<std::string, int>> vec;

    for (auto pair : buffer_map) {
        vec.emplace_back(pair.first, pair.second);
    }

    return vec;
}

sge::core::debug::Profiler::Profiler() {
    last_dump_time = std::chrono::steady_clock::now();
}

std::string sge::core::debug::Profiler::get_string() {
    std::string s;

    float counted_time = total_dump_time / 1000000.0;

    s += "Total: " + std::to_string(counted_time) + "\n";

    for (auto pair : dump_map) {
        s += pair.first + ": " + std::to_string(pair.second / 1000000.0) + "\n";
    }

    return s;
}


void sge::core::debug::Profiler::draw(sf::RenderTarget &target, sf::RenderStates states, int screen_width, int screen_height) {

    sf::RectangleShape background_rect(sf::Vector2f(screen_width, SGE_DEBUG_PROFILER_BAR_HEIGHT));
    background_rect.setPosition(0, screen_height - SGE_DEBUG_PROFILER_BAR_HEIGHT);
    background_rect.setFillColor(sf::Color(80, 80, 80));

    target.draw(background_rect, states);

    float horizontal_anchor = 0;
    int count = 0;
    for (auto id : SGE_DEBUG_PROFILER_ORDER) {

        float fraction = dump_map[id] / (float)total_dump_time;
        sf::RectangleShape rect(sf::Vector2f(screen_width*fraction, SGE_DEBUG_PROFILER_BAR_HEIGHT));
        rect.setPosition(horizontal_anchor, screen_height - SGE_DEBUG_PROFILER_BAR_HEIGHT);

        rect.setFillColor(sf::Color(255*fraction, 80*fraction, 80*fraction));

        target.draw(rect, states);

        count++;
    }
}





