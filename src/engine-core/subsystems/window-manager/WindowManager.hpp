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
#include <chrono>
#include "SGE/components/Polygon.hpp"
#include "ComponentCreator.hpp"
#include "SFML/Graphics.hpp"
#include "SGE/engine/construction_data/WindowManager_ConstructionData.hpp"

namespace sge {
    namespace core {
        /*!
         * \brief The Subsystem that manages the window and in general the video output of the engine.
         */
        class WindowManager : public Subsystem {
        public:
            /*!
             * \brief Constructor
             * \param data The object containing all the used defined data necessary to build this object
             */
            WindowManager(const cd::WindowManager_ConstructionData& data);
            /*!
             * \brief Handles the SFML events related to the window
             */
            void handle_window_events();
            /*!
             * \brief Checks if the window is open
             * \return true if the window is open, false otherwise
             */
            bool window_is_open() { return m_window.isOpen(); }
            /*!
             * \brief Exposes the clear method of the managed window
             */
            void clear_window() { m_window.clear(sf::Color::Black); }
            /*!
             * \brief Exposes the display method of the managed window
             */
            void display() { m_window.display(); }

            void draw();

        private:
            sf::RenderWindow m_window;

            ComponentCreator<cmp::Polygon> polygon_component_creator;

            sf::View m_view;
            sf::RenderStates m_render_states;
        };
    }
}




#endif //FACTORY_EXPERIMENTS_WINDOWMANAGER_HPP
