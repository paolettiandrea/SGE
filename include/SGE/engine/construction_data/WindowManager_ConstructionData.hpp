#ifndef SGE_WINDOWMANAGER_CONSTRUCTIONDATA_HPP
#define SGE_WINDOWMANAGER_CONSTRUCTIONDATA_HPP

#include <string>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Window/ContextSettings.hpp>

namespace sge::cd {
    /*!
     * \brief Contains all the user dependent data necessary to build the window aspect of the engine
     */
    struct WindowManager_ConstructionData {
        WindowManager_ConstructionData() {
            context_settings.antialiasingLevel = 8;
        }
        /*!
         * \brief The title of the window
         */
        std::string window_title = "My window";
        /*!
         * \brief The width of the window in pixels
         */
        unsigned int window_width = 880;
        /*!
         * \brief The height of the window in pixels
         */
        unsigned int window_height = 495;
        /*!
         * \brief The x position of the top-left angle of the window
         */
        int window_pos_x = 10;
        /*!
         * \brief The y position of the top-left angle of the window
         */
        int window_pos_y = 10;

        bool vsync_on = true;

        sf::ContextSettings context_settings;

        bool fullscreen_on = true;

        std::vector<std::string> layers = { "Background" };

    };
}


#endif //SGE_WINDOWMANAGER_CONSTRUCTIONDATA_HPP
