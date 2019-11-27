#ifndef NON_GRAVITAR_PROFILER_HPP
#define NON_GRAVITAR_PROFILER_HPP


#include <string>
#include <map>
#include <chrono>
#include <vector>
#include <SFML/Graphics.hpp>



            class Profiler : sf::Drawable {
            public:
                Profiler();
                void start(const std::string& id);
                void stop(const std::string& id);
                void dump ();

                std::string get_string();

                std::vector<std::pair<std::string, int>> get_count();

            private:
                void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

                std::chrono::time_point<std::chrono::steady_clock> last_dump_time;

                std::map<std::string, std::chrono::time_point<std::chrono::steady_clock>>  starting_time_map;
                std::map<std::string, int> buffer_map;
                std::map<std::string, int> dump_map;
                int total_dump_time;        // in microsecs, comprehensive of the not recorded time

            };




#endif //NON_GRAVITAR_PROFILER_HPP
