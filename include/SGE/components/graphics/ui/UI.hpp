#ifndef NON_GRAVITAR_UI_HPP
#define NON_GRAVITAR_UI_HPP

#include "SGE/components/Component.hpp"
#include <SFML/Graphics.hpp>
#include <SGE/Vec2.hpp>
#include "blocks/UIContent.hpp"


namespace sge {
    namespace core { class WindowManager; }
    namespace cmp {
        class UI : public Component<UI> , public sf::Drawable{
        public:

            enum VerticalAlignment {TOP, CENTER, BOTTOM};
            enum HotizontalAlignment {LEFT, MIDDLE, RIGHT};

            struct Alignment {
                Alignment() {
                    this->horizontal = MIDDLE;
                    this->vertical = CENTER;
                }
                Alignment(HotizontalAlignment horizontal, VerticalAlignment vertical) {
                    this->horizontal = horizontal;
                    this->vertical = vertical;
                }
                VerticalAlignment vertical;
                HotizontalAlignment horizontal;
            };


            explicit UI (const utils::Handle<GameObject> &gameobject);

            void set_anchor_alignment(Alignment alignment);

            void set_anchor_alignment(HotizontalAlignment horizontal, VerticalAlignment vertical_alignment);
            void set_origin_alignment(HotizontalAlignment horizontal, VerticalAlignment vertical_alignment);
            void set_origin_alignment(Alignment alignment);

            void set_content(UIContent* content);

            void initialization_callback() override;

            void destruction_callback() override;

            std::string get_debug_string() override;

        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

            void clean_dirty_origin_alignment();
            void clean_dirty_anchor_alignment(sf::FloatRect new_rect);
            void clean_font(core::FontManager& font_manager);

            Alignment anchor_align;

            bool dirty_anchor_alignment = true;
            Alignment origin_align;

            bool dirty_origin_alignment = true;

            UIContent* m_content = nullptr;

            utils::event::EventHandler camera_ratio_changed_evhandler;      // makes dirty the anchor alignment flag


            void visual_debug_draw_ui_rectangles(sf::RenderTexture& target);

            friend class core::WindowManager;
        };
    }
}



#endif //NON_GRAVITAR_UI_HPP
