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


            bool is_mouse_down(sf::Mouse::Button button);
            bool is_mouse_released(sf::Mouse::Button button);
            bool is_mouse_pressed(sf::Mouse::Button button);

            /**
             * \brief Prints the three mouse button maps (down/pressed/released)
             */
            void print_mousemaps();



            bool is_key_down(sf::Keyboard::Key key);
            bool is_key_pressed(sf::Keyboard::Key key);
            bool is_key_released(sf::Keyboard::Key key);

            /**
             * \brief Resets the volatile properties, meaning the ones that last only one frame (pressed and released).
             */
            void reset_volatile();

            /**
             * \brief Prints the three keyboard maps (down/pressed/released)
             */
            void print_keymaps();

            // Callbacks for the sfml events to use at the start of the game loop
            void pressed_key_callback(sf::Keyboard::Key key);
            void released_key_callback(sf::Keyboard::Key key);
            void pressed_mouse_callback(sf::Mouse::Button button);
            void released_mouse_callback(sf::Mouse::Button button);

            void memory_buffer_pass() override;


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
