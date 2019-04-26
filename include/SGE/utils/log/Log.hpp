
#ifndef SGE_LOG_HPP
#define SGE_LOG_HPP

#include <sstream>

/*!
\file
\brief Header file
*/

namespace utils {
    namespace log {

        class Loggable;

/*!
 * Object that allows for some simple level-based logging functionality.
 *
 */
        class Log {
        public:
            Log() : message_level(-3) {};
            virtual ~Log();
            std::ostringstream& Get(Loggable* logger, int level = 0);

        protected:
            std::ostringstream os;

        private:
            Log(const Log&);
            Log& operator =(const Log&);
            int message_level;

        };



/*!
 * Macro that allows to create and use a Log object only if the given level is high enough,
 * if not basically the object is not even created, so there shouldn't be overhead at all.
 */
#define LOG(level) \
if ((level) > LOG_MAX_LEVEL) ;\
else utils::log::Log().Get(this, level)


#define LOG_ERROR               LOG(-2)
#define LOG_WARNING             LOG(-1)
#define LOG_INFO                LOG(0)
#define LOG_DEBUG(debug_level)  LOG((debug_level))

    }
}


#endif //PROJECT_LOG_HPP
