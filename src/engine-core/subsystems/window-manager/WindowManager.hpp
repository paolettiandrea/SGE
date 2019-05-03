//
// Created by andrea on 5/3/19.
//

#ifndef FACTORY_EXPERIMENTS_WINDOWMANAGER_HPP
#define FACTORY_EXPERIMENTS_WINDOWMANAGER_HPP

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/
#include "Subsystem.hpp"
#include "SFML/Graphics.hpp"
#include "SGE/engine/construction_data/WindowManager_ConstructionData.hpp"

namespace sge {
    namespace core {
        /*!
         * \brief The Subsystem that manages the window and in general the video output of the engine.
         */
        class WindowManager : public Subsystem {
        public:
            WindowManager(const cd::WindowManager_ConstructionData& data);

            void handle_window_events();
            bool window_is_open() { return m_window.isOpen(); }
            void clear_window() { m_window.clear(sf::Color::Black); }
            void display() { m_window.display(); }

        private:
            sf::RenderWindow m_window;
        };
    }
}




#endif //FACTORY_EXPERIMENTS_WINDOWMANAGER_HPP
