//
// Created by andrea on 6/16/19.
//

#ifndef SGE_DIRECTIONDEBUGSHAPE_HPP
#define SGE_DIRECTIONDEBUGSHAPE_HPP

#include <SGE/Vec2.hpp>
#include "DebugShape.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge::debug {
    class DirectionDebugShape : public DebugShape {
    public:
        DirectionDebugShape(sge::Vec2<float> from, sge::Vec2<float> to, float duration, sf::Color color=SGE_DEFAULT_DEBUG_COLOR) : DebugShape(duration), arrow_vert_array(sf::PrimitiveType::Lines) {
            arrow_vert_array.append(sf::Vertex(sf::Vector2f(from.x,-from.y),color));
            arrow_vert_array.append(sf::Vertex(sf::Vector2f(to.x,-to.y),color));

            float lenght = (to - from).get_magnitude();
            auto arrow_segments_dir = from-to;
            arrow_segments_dir.set_magnitude(lenght*0.1f);

            auto left = Vec2<float>::rotate(arrow_segments_dir,M_PI/6);
            arrow_vert_array.append(sf::Vertex(sf::Vector2f(to.x,-to.y),color));
            arrow_vert_array.append(sf::Vertex(sf::Vector2f(to.x+left.x,-to.y-left.y),color));

            auto right = Vec2<float>::rotate(arrow_segments_dir,-M_PI/6);
            arrow_vert_array.append(sf::Vertex(sf::Vector2f(to.x,-to.y),color));
            arrow_vert_array.append(sf::Vertex(sf::Vector2f(to.x+right.x,-to.y-right.y),color));
        }
        void update_dimensions(float vertical_view_size) override;

    protected:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    private:
        sf::VertexArray arrow_vert_array;
    };
}



#endif //SGE_DIRECTIONDEBUGSHAPE_HPP
