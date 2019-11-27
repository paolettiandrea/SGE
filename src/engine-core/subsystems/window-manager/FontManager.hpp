#ifndef NON_GRAVITAR_FONTMANAGER_HPP
#define NON_GRAVITAR_FONTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <SGE/utils/log/Loggable.hpp>

namespace  sge {
    namespace  core {
    class FontManager : public utils::log::Loggable {
        public:
        FontManager();

        virtual ~FontManager();

        sf::Font* get_font(std::string font_name);
            void load_fonts();

        private:
            void load_font(const std::string& font_path);

            std::map<std::string, sf::Font*> loaded_fonts;
        };
    }
}



#endif //NON_GRAVITAR_FONTMANAGER_HPP
