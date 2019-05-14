//
// Created by andrea on 5/14/19.
//

#ifndef FACTORY_EXPERIMENTS_POINTDEBUGSHAPE_HPP
#define FACTORY_EXPERIMENTS_POINTDEBUGSHAPE_HPP

#include "SGE/debug/DebugShape.hpp"

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace  sge {
    namespace debug {
        class PointDebugShape : public DebugShape {
        public:
            PointDebugShape(float x, float y, float duration);

        protected:
            void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

        private:
            sf::CircleShape m_dot_shape;
        };
    }
}



#endif //FACTORY_EXPERIMENTS_POINTDEBUGSHAPE_HPP
