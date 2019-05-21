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
    namespace core {
        class DebugShapesManager;
    }

    namespace debug {
        /*!
         * \brief A shape used to represent some debug information visually.
         * \details
         * It's basically an sf::Drawable with a time duration (in s) associated with it and used internally by the
         * engine in order to know how long to display it before discarding it
         */
        class DebugShape : public sf::Drawable {
            friend class core::DebugShapesManager;
        public:
            explicit DebugShape(float duration = 0.f);

            bool is_discardable();

            virtual void update_dimensions(float vertical_view_size) = 0;

        protected:
            static sf::Color primary_debug_color;
            sf::Font debug_font;

            virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const = 0;
            virtual void internal_initialization(const sf::Font& debug_font);

        private:

            std::chrono::time_point<std::chrono::steady_clock> discard_time_point;


    };
    }
}



#endif //FACTORY_EXPERIMENTS_DEBUGSHAPE_HPP
