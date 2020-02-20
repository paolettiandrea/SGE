#ifndef NON_GRAVITAR_PROFILER_HPP
#define NON_GRAVITAR_PROFILER_HPP


#include <string>
#include <map>
#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>

#define SGE_DEBUG_PROFILER_ORDER { "Fixed Update", "Physics", "Update", "Draw", "Display", "Debug"}
#define SGE_DEBUG_PROFILER_SAMPLE_FRAMES_NUMBER 3
#define SGE_DEBUG_PROFILER_BAR_HEIGHT 10

namespace sge {
    namespace core {
        namespace debug {
            class Profiler {
            public:
                Profiler();
                void start(const std::string& id);
                void stop(const std::string& id);
                void increase_dump_counter();

                std::string get_string();

                std::vector<std::pair<std::string, int>> get_count();

                void draw(sf::RenderTarget& target, sf::RenderStates states, int screen_width,int screen_height);

            private:
                unsigned int m_dump_counter = 0;

                std::chrono::time_point<std::chrono::steady_clock> last_dump_time;

                std::map<std::string, std::chrono::time_point<std::chrono::steady_clock>>  starting_time_map;
                std::map<std::string, int> buffer_map;
                std::map<std::string, int> dump_map;
                int total_dump_time;        // in microsecs, comprehensive of the not recorded time

            };
        }
    }
}





#endif //NON_GRAVITAR_PROFILER_HPP
