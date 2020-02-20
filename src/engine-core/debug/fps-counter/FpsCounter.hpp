#ifndef NON_GRAVITAR_FPSCOUNTER_HPP
#define NON_GRAVITAR_FPSCOUNTER_HPP


#define SGE_DEBUG_FPS_COUNTER_CHAR_SIZE 25
#define SGE_DEBUG_FPS_COUNTER_RIGHT_OFFSET 70
#define SGE_DEBUG_FPS_COUNTER_TOP_PADDING 20
#define SGE_DEBUG_FPS_COUNTER_REFRESH_PERIOD 0.3

#include <SFML/Graphics.hpp>
#include "subsystems/window-manager/FontManager.hpp"
#include <chrono>
namespace sge { namespace core { namespace debug {
    class FpsCounter : public sf::Drawable {
    public:
        FpsCounter(FontManager& font_manager){
            font = font_manager.get_font("RobotoMono-Medium");
            text.setString("0.0");
            text.setFont(*font);
            text.setCharacterSize(SGE_DEBUG_FPS_COUNTER_CHAR_SIZE);
            text.setFillColor(sf::Color::White);
            text.setOutlineThickness(2);
            text.setOutlineColor(sf::Color::Black);

            last_count_tp = std::chrono::steady_clock::now();
            last_flush_tp = std::chrono::steady_clock::now();
        }

        void update_x_pos(sf::RenderTarget& target) {
            text.setPosition(target.getSize().x - SGE_DEBUG_FPS_COUNTER_RIGHT_OFFSET, SGE_DEBUG_FPS_COUNTER_TOP_PADDING);
        }

        void count_frame();
    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        sf::Font* font;
        sf::Text text;

        unsigned int frame_counter = 0;
        std::chrono::time_point<std::chrono::steady_clock> last_flush_tp;
        std::chrono::time_point<std::chrono::steady_clock> last_count_tp;
    };
} } }


#endif //NON_GRAVITAR_FPSCOUNTER_HPP
