#ifndef NON_GRAVITAR_UICONTENT_HPP
#define NON_GRAVITAR_UICONTENT_HPP


#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SGE/utils/log/Loggable.hpp>


namespace sge {
    namespace core {class FontManager;}
    namespace cmp {class UI;}

class UIContent : public sf::Drawable {
        friend class cmp::UI;
    public:
        UIContent() : m_offset(0,0) {}
        virtual void set_position(sf::Vector2f position) = 0;
        virtual void set_origin(sf::Vector2f origin) = 0;
        virtual sf::FloatRect get_bounds() = 0;

        virtual void clean_font(core::FontManager& font_manager) {}
        virtual void prepare_for_draw() {}

        void set_offset(const sf::Vector2f& new_offset) {
            if (new_offset != m_offset) {
                m_offset = new_offset;
                make_bounds_dirty();
            }
        }


    protected:
        // Needs to be called by child classes when the needed bounds change
        void make_bounds_dirty() { m_bounds_dirty = true; }

    private:
        bool m_bounds_dirty = true;

        sf::Vector2f m_offset;
    };
}



#endif //NON_GRAVITAR_UICONTENT_HPP
