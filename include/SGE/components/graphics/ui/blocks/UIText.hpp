#ifndef NON_GRAVITAR_UITEXT_HPP
#define NON_GRAVITAR_UITEXT_HPP

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include "UIContent.hpp"

namespace  sge {
    class UIText : public UIContent {
    public:
        explicit UIText(const std::string &text, const std::string &font_id, unsigned int character_size);


        void set_size(unsigned int character_size);
        void set_font(const std::string& font_id);


        void set_position(sf::Vector2f position) override;
        void set_origin(sf::Vector2f origin) override;
        sf::FloatRect get_bounds() override;
        void clean_font(core::FontManager &font_manager) override;
        void set_spacing(float factor);

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        sf::Text m_text;

        std::string m_font_id;
        bool dirty_font = true;
    };
}



#endif //NON_GRAVITAR_UITEXT_HPP
