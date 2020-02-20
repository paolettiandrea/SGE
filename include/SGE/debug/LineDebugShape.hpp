#ifndef SGE_LINEDEBUGSHAPE_HPP
#define SGE_LINEDEBUGSHAPE_HPP

#include "SGE/debug/DebugShape.hpp"
#include "SGE/debug/PointDebugShape.hpp"

namespace sge {
    namespace debug {
        class LineDebugShape : public DebugShape {
        public:
            LineDebugShape(float x1, float y1, float x2, float y2, float duration=0.f, unsigned int coord_decimals=1,
                           const std::string &label = "", sf::Color color=SGE_DEFAULT_DEBUG_COLOR);

            void update_dimensions(float vertical_view_size) override;

        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
            void internal_initialization(const sf::Font &debug_font) override;

        private:
            PointDebugShape m_point1_debug_shape;
            PointDebugShape m_point2_debug_shape;
            sf::RectangleShape line_rect;
            sf::VertexArray line_vertarray;
        };

    }
}

#endif //SGE_LINEDEBUGSHAPE_HPP
