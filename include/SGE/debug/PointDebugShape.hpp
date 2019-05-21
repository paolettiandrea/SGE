//
// Created by andrea on 5/14/19.
//

#ifndef FACTORY_EXPERIMENTS_POINTDEBUGSHAPE_HPP
#define FACTORY_EXPERIMENTS_POINTDEBUGSHAPE_HPP

#include <SGE/Vec2.hpp>
#include "SGE/debug/DebugShape.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace  sge {
    namespace debug {
        class LineDebugShape;
        class PointDebugShape : public DebugShape {
            friend class LineDebugShape;
        public:
            PointDebugShape(float x, float y, float duration = 0.f, const std::string& label = "", unsigned int coords_digits=1);

            void update_dimensions(float new_vertical_screen_size) override;

        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        private:
            sf::Text m_coordinates_text;

            sf::VertexArray cross_vertarray;
            sge::Vec2<float> pos_vec;
        };
    }
}



#endif //FACTORY_EXPERIMENTS_POINTDEBUGSHAPE_HPP
