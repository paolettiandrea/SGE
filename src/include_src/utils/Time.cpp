#include "Time.hpp"

namespace utils {
    namespace time {

        // TEMP
        const static std::chrono::time_point<std::chrono::steady_clock>
                execution_start_time_point= std::chrono::steady_clock::now();



        std::string get_hi_res_time_stamp() {
            using  namespace std::chrono;
            time_point<steady_clock> now_time_point = steady_clock::now();
            duration<double, std::ratio<1>> t = now_time_point -  execution_start_time_point;

            return std::to_string(t.count());

        }

    }
}
