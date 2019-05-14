//
// Created by andrea on 5/14/19.
//

#ifndef FACTORY_EXPERIMENTS_DEBUGSHAPE_HPP
#define FACTORY_EXPERIMENTS_DEBUGSHAPE_HPP

#include "SFML/Graphics.hpp"
#include <chrono>

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
namespace sge {
    namespace debug {
        /*!
         * \brief A shape used to represent some debug information visually.
         * \details
         * It's basically an sf::Drawable with a time duration (in s) associated with it and used internally by the
         * engine in order to know how long to display it before discarding it
         */
        class DebugShape : public sf::Drawable {
        public:
            DebugShape(float duration);

            bool is_discardable();

        protected:
            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;

        private:
            std::chrono::time_point<std::chrono::steady_clock> discard_time_point;

    };
    }
}



#endif //FACTORY_EXPERIMENTS_DEBUGSHAPE_HPP
