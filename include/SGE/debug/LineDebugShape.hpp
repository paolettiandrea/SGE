#ifndef FACTORY_EXPERIMENTS_LINEDEBUGSHAPE_HPP
#define FACTORY_EXPERIMENTS_LINEDEBUGSHAPE_HPP

#include "SGE/debug/DebugShape.hpp"
#include "SGE/debug/PointDebugShape.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace debug {
        class LineDebugShape : public DebugShape {
        public:
            LineDebugShape(float x1, float y1, float x2, float y2, float duration, unsigned int coord_decimals);

            void update_dimensions(float vertical_view_size) override;

        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
            void internal_initialization(const sf::Font &debug_font) override;

        private:
            PointDebugShape m_point1_debug_shape;
            PointDebugShape m_point2_debug_shape;
            sf::RectangleShape line_rect;
        };

    }
}


#endif //FACTORY_EXPERIMENTS_LINEDEBUGSHAPE_HPP
