#ifndef LOG_ID_MAX_WIDTH
#define LOG_ID_MAX_WIDTH 46
#endif

#include "Log.hpp"

#include "Loggable.hpp"
#include "Terminal.hpp"


namespace utils {
    namespace log {

        std::ostringstream& Log::Get(Loggable* logger, int level)
        {
            this->message_level = level;
            const terminal::Color* color;

            switch (level){
                case -2 :
                    // ERRORS
                    color = &terminal::Color::RED;
                    break;
                case -1:
                    // WARNINGS
                    color = &terminal::Color::LIGHT_BROWN;
                    break;
                case 0:
                    // INFOS
                    color = &terminal::Color::BLUE;
                    break;
                case 1:
                    // DEBUG(1)
                    color = &terminal::Color::DEFAULT;
                    break;
                default:
                    // DEBUG(n)
                    color = &terminal::Color::DARK_GRAY;
                    break;
            }

            std::string id_string = logger->get_log_id();
            if (id_string.length() > LOG_ID_MAX_WIDTH) {
                id_string.erase(LOG_ID_MAX_WIDTH-1, std::string::npos);
                id_string = " " + id_string;
            } else {
                id_string = std::string(LOG_ID_MAX_WIDTH - id_string.length(), ' ') + id_string;
            }
            id_string += " ";
#ifdef LOG_PRINT_HEADER
            std::string logger_header_string = "L:[" + std::to_string(message_level) + "]\t" + logger->get_logger_header();
            os << terminal::TextMod(*color, terminal::Style::FAINT) << logger_header_string << std::endl << terminal::TextMod(terminal::Color::RESET);
#endif
            os << terminal::TextMod(*color, terminal::Style::INVERSE) << id_string
               << terminal::TextMod(terminal::Color::DARK_GRAY, terminal::Style::INVERSE_OFF)
               << " > " << terminal::TextMod(terminal::Color::RESET);
            return os;
        }

        Log::~Log()
        {
            os << std::endl;
            fprintf(stdout, "%s", os.str().c_str());
            fflush(stdout);
        }
    }
}
