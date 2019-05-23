//
// Created by andrea on 5/3/19.
//

#ifndef FACTORY_EXPERIMENTS_WINDOWMANAGER_HPP
#define FACTORY_EXPERIMENTS_WINDOWMANAGER_HPP

/*!
\file
\brief ${BRIEF_FILE_DESCRIPTION}
*/

#include <chrono>
#include <SGE/components/VertArray.hpp>
#include "SFML/Graphics.hpp"

#include "Subsystem.hpp"
#include "VertArray.hpp"
#include "ComponentCreator.hpp"
#include "WindowManager_ConstructionData.hpp"
#include "DebugShapesManager.hpp"
#include "Camera.hpp"

namespace sge {
    namespace core {
        /*!
         * \brief The Subsystem that manages the window and in general the video output of the engine.
         */
        class WindowManager : public Subsystem {
            friend class EngineCore;
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
            void display() {
                debug_shapes_manager.normalize_shapes_to_screen_size(m_camera.m_vertical_size);
                m_window.draw(debug_shapes_manager,sf::RenderStates::Default);

                m_window.display();

                debug_shapes_manager.remove_expired_shapes();

                
            }

            void draw();


        private:
            sf::RenderWindow m_window;

            ComponentCreator<cmp::VertArray> vertarray_component_creator;

            sf::RenderStates m_render_states;

            DebugShapesManager debug_shapes_manager;
            Camera m_camera;
        };
    }
}




#endif //FACTORY_EXPERIMENTS_WINDOWMANAGER_HPP
