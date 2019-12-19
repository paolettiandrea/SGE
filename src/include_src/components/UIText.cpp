#include "SGE/components/graphics/ui/blocks/UIText.hpp"
#include "FontManager.hpp"

namespace sge {
    UIText::UIText(const std::string &text, const std::string &font_id, unsigned int character_size) {
        m_text.setString(text);
        set_font(font_id);
        set_size(character_size);
    }

    void UIText::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        target.draw(m_text, states);
    }

    void UIText::set_position(sf::Vector2f position) {
        m_text.setPosition(position);
    }

    void UIText::set_origin(sf::Vector2f origin) {
        m_text.setOrigin(origin);
    }

    sf::FloatRect UIText::get_bounds() {
        return m_text.getLocalBounds();
    }

    void UIText::set_font(const std::string& font_id) {
        if (m_font_id != font_id) {
            m_font_id = font_id;
            dirty_font = true;
            make_bounds_dirty();
        }
    }

    void UIText::clean_font(core::FontManager &font_manager) {
        if (dirty_font) {
            m_text.setFont(*font_manager.get_font(m_font_id));
            dirty_font = false;
        }
    }

    void UIText::set_size(unsigned int character_size) {
        m_text.setCharacterSize(character_size);
        make_bounds_dirty();
    }

    void UIText::set_spacing(float factor) {
        m_text.setLetterSpacing(factor);
        make_bounds_dirty();
    }

    void UIText::set_string(const std::string &new_string) {
        m_text.setString(new_string);
        make_bounds_dirty();
    }
}

