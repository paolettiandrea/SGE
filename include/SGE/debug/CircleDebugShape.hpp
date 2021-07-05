//
// Created by andrea on 6/16/19.
//

#ifndef SGE_CIRCLEDEBUGSHAPE_HPP
#define SGE_CIRCLEDEBUGSHAPE_HPP

#include <SGE/Vec2.hpp>
#include "DebugShape.hpp"
#include "PointDebugShape.hpp"

#define CIRCLE_DEBUG_SHAPE_LINES 1000

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge::debug {
    class CircleDebugShape : public DebugShape {
    public:
        CircleDebugShape(sge::Vec2<float> center, float radius, float durtion, const std::string& label, unsigned int decimals, sf::Color color=SGE_DEFAULT_DEBUG_COLOR)
            : DebugShape(durtion), circle_vert_array(sf::PrimitiveType::LineStrip), center_point_debug_shape(center.x,center.y,durtion,label,decimals, color) {
            float angle_step = M_PI*2/CIRCLE_DEBUG_SHAPE_LINES;
            for (int i = 0; i < CIRCLE_DEBUG_SHAPE_LINES; ++i) {
                circle_vert_array.append(sf::Vertex(sf::Vector2f(cosf(angle_step*i)*radius+center.x,-sinf(angle_step*i)*radius-center.y),color));
            }
        }
        void update_dimensions(float vertical_view_size) override;

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

        void internal_initialization(const sf::Font& debug_font) override;

    private:
        sf::VertexArray circle_vert_array;
        PointDebugShape center_point_debug_shape;
    };
}



#endif //SGE_CIRCLEDEBUGSHAPE_HPP
