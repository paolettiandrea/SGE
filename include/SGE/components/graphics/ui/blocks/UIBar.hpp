#ifndef NON_GRAVITAR_UIBAR_HPP
#define NON_GRAVITAR_UIBAR_HPP


#include <vector>
#include <SFML/Graphics.hpp>
#include "UIContent.hpp"

namespace sge {
    class UIBar : public UIContent {
    public:
        UIBar(float width, float height);

        void set_position(sf::Vector2f position) override;
        void set_origin(sf::Vector2f origin) override;
        sf::FloatRect get_bounds() override;

        void set_bar(float filled_factor);

        void prepare_for_draw() override;

        void set_background_color(sf::Color color);
        void set_bar_color(sf::Color color);

    protected:

        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        float height, width;
        float m_filled_factor = 0.5;

        sf::Vector2f m_origin, m_position;

        sf::VertexArray bar_rectangle;
        sf::VertexArray background_rectangle;
        bool dirty_geometry = true;

        void clean_geometry();
    };
}



#endif //NON_GRAVITAR_UIBAR_HPP
