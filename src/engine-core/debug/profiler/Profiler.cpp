#include <iostream>
#include "Profiler.hpp"


            void Profiler::start(const std::string &id) {
                if (starting_time_map.count(id)==0) {
                    starting_time_map[id] = std::chrono::steady_clock::now();
                } else {
                    std::cerr << id << " was already started" << std::endl;
                    exit(1);
                }
            }

            void Profiler::stop(const std::string &id) {
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

            void Profiler::dump() {

                auto delta = std::chrono::steady_clock::now() - last_dump_time;
                total_dump_time = std::chrono::duration_cast<std::chrono::microseconds>(delta).count();

                for (auto pair : buffer_map) {
                    if (dump_map[pair.first]>0) dump_map[pair.first] += pair.second;
                    else dump_map[pair.first] = pair.second;
                }
                buffer_map.clear();

                last_dump_time = std::chrono::steady_clock::now();
            }

            std::vector<std::pair<std::string, int>> Profiler::get_count() {
                std::vector<std::pair<std::string, int>> vec;

                for (auto pair : buffer_map) {
                    vec.emplace_back(pair.first, pair.second);
                }

                return vec;
            }

            Profiler::Profiler() {
                last_dump_time = std::chrono::steady_clock::now();
            }

            std::string Profiler::get_string() {
                std::string s;

                float counted_time = total_dump_time / 1000000.0;

                s += "Total: " + std::to_string(total_dump_time);

                return s;
            }

            void Profiler::draw(sf::RenderTarget &target, sf::RenderStates states) const {

            }



