//
// Created by andrea on 4/9/19.
//

#ifndef PROJECT_TERMINAL_HPP
#define PROJECT_TERMINAL_HPP


#include <ostream>

namespace utils {
    namespace terminal {

#define TERMINAL_FALLBACK_WIDTH 170;



        /*!
         * Class that defines the available terminal colors.
         */
        class Color {
        private:
            /*!
             * The string specifying the platform-specific code necessary to set the terminal output to a specific color
             */
            std::string color_code;
        public:
            const std::string &get_color_code() const;

        public:
            explicit Color(const std::string& platform_specific_color_code);

            // The available colors

            static const Color RESET;
            static const Color DEFAULT;
            static const Color WHITE;
            static const Color BLACK;
            static const Color RED;
            static const Color GREEN;
            static const Color BROWN;
            static const Color BLUE;
            static const Color MAGENTA;
            static const Color CYAN;
            static const Color LIGHT_GRAY;
            static const Color DARK_GRAY;
            static const Color LIGHT_RED;
            static const Color LIGHT_GREEN;
            static const Color LIGHT_BROWN;
            static const Color LIGHT_BLUE;
            static const Color LIGHT_MAGENTA;
            static const Color LIGHT_CYAN;
        };

        class Style {

        private:
            /*!
             * The string specifying the platform-specific code necessary to set the terminal output to a specific color
             */
            std::string color_code;
        public:
            const std::string &get_color_code() const;

        public:
            explicit Style(const std::string& platform_specific_color_code);

            static const Style BOLD;
            static const Style FAINT;
            static const Style ITALICS;
            static const Style UNDERLINE;
            static const Style BLINK;
            static const Style INVERSE;
            static const Style HIDDEN;
            static const Style STRIKE;
            static const Style BOLD_OFF;
            static const Style ITALICS_OFF;
            static const Style UNDERLINE_OFF;
            static const Style INVERSE_OFF;
            static const Style STRIKE_OFF;
        };

        class TextMod {
            std::string color_string;
        public:
            explicit TextMod (Color color);

            TextMod (Color color, Style style);

            explicit TextMod(Style style);

            friend std::ostream&
            operator<<(std::ostream& os, const TextMod& mod) {
                return os << mod.color_string;
            }
        };



        static unsigned int get_terminal_width();
    }

}


#endif //PROJECT_TERMINAL_HPP
