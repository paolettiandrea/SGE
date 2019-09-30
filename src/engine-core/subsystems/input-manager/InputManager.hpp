//
// Created by andrea on 29/09/19.
//

#ifndef SGE_INPUTMANAGER_HPP
#define SGE_INPUTMANAGER_HPP


#include <SFML/Window/Keyboard.hpp>
#include "Subsystem.hpp"

namespace sge {
    namespace  core {
        /*!
        * \brief The Subsystem that manages basic inputs: keyboard and mouse.
        */
        class InputManager : public Subsystem {
        public:
            InputManager();

            /**
             * \brief Check if the button is pressed this frame
             * \param button The mouse button that needs to be checked
             */
            bool is_mouse_down(sf::Mouse::Button button);
            /**
             * Check if the button was released this frame (it was pressed the frame before and now it's not)
             * @param button
             */
            bool is_mouse_released(sf::Mouse::Button button);
            bool is_mouse_pressed(sf::Mouse::Button button);
            void print_mousemaps();



            bool is_key_down(sf::Keyboard::Key key);
            bool is_key_pressed(sf::Keyboard::Key key);
            bool is_key_released(sf::Keyboard::Key key);

            /**
             * \brief Resets the volatile properties, meaning the ones that last only one frame (pressed and released).
             */
            void reset_volatile();

            void print_keymaps();

            void pressed_key_callback(sf::Keyboard::Key key);
            void released_key_callback(sf::Keyboard::Key key);
            void pressed_mouse_callback(sf::Mouse::Button button);
            void released_mouse_callback(sf::Mouse::Button button);


        private:
            bool down_keymap[sf::Keyboard::KeyCount] = {false};
            bool pressed_keymap[sf::Keyboard::KeyCount] = {false};
            bool released_keymap[sf::Keyboard::KeyCount] = {false};

            bool down_mousemap[sf::Mouse::ButtonCount] = {false};
            bool pressed_mousemap[sf::Mouse::ButtonCount] = {false};
            bool released_mousemap[sf::Mouse::ButtonCount] = {false};
        };
    }
}


#endif //SGE_INPUTMANAGER_HPP
