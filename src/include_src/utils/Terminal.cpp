//
// Created by andrea on 4/9/19.
//

#include "Terminal.hpp"
#include <sys/ioctl.h>



namespace utils {
    namespace terminal {

        Color::Color(const std::string& platform_specific_color_code) {
            color_code = platform_specific_color_code;
        }

        const std::string &Color::get_color_code() const {
            return color_code;
        }

        const Color Color::RESET("0");
        const Color Color::DEFAULT("39");
        const Color Color::WHITE("97");
        const Color Color::BLACK("30");
        const Color Color::RED("31");
        const Color Color::GREEN("32");
        const Color Color::BROWN("33");
        const Color Color::BLUE("34");
        const Color Color::MAGENTA("35");
        const Color Color::CYAN("36");
        const Color Color::LIGHT_GRAY("37");
        const Color Color::DARK_GRAY("90");
        const Color Color::LIGHT_RED("91");
        const Color Color::LIGHT_GREEN("92");
        const Color Color::LIGHT_BROWN("93");
        const Color Color::LIGHT_BLUE("94");
        const Color Color::LIGHT_MAGENTA("95");
        const Color Color::LIGHT_CYAN("96");

        const Style Style::BOLD("1");
        const Style Style::FAINT("2");
        const Style Style::ITALICS("3");
        const Style Style::UNDERLINE("4");
        const Style Style::BLINK("5");
        const Style Style::INVERSE("7");
        const Style Style::HIDDEN("8");
        const Style Style::STRIKE("9");
        const Style Style::BOLD_OFF("22");
        const Style Style::ITALICS_OFF("23");
        const Style Style::UNDERLINE_OFF("24");
        const Style Style::INVERSE_OFF("27");
        const Style Style::STRIKE_OFF("29");

        const std::string &Style::get_color_code() const {
            return color_code;
        }

        Style::Style(const std::string &platform_specific_color_code) {
            color_code = platform_specific_color_code;
        }


#if __linux__

        static unsigned int get_terminal_width() {
            struct winsize w;
            ioctl(0, TIOCGWINSZ, &w);
            unsigned int columns = w.ws_col;
            // Since this returns strange values if run from some IDEs (0 or really high values), in that case return a fallback value
            if (columns >0 && columns < 300) return columns;
            else return TERMINAL_FALLBACK_WIDTH;
        }

        TextMod::TextMod(Color color) {
            color_string = "\033[" + color.get_color_code() + "m";
        }

        TextMod::TextMod(Color color, Style style) {
            color_string = "\033[" + style.get_color_code() + ";" + color.get_color_code() + "m";
        }

        TextMod::TextMod(Style style) {
            color_string = "\033[" + style.get_color_code() + "m";
        }

#else
        static unsigned int get_terminal_width() {
            return TERMINAL_FALLBACK_WIDTH;
        }

        TextMod::TextMod(Color color) {
            color_string = "";
        }

        TextMod::TextMod(Color color, Style style) {
            color_string = "";
        }

        TextMod::TextMod(Style style) {
            color_string = "";
        }
#endif


    }
}