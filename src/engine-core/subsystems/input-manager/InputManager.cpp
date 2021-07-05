#include <SFML/Window/Mouse.hpp>
#include "InputManager.hpp"

void sge::core::InputManager::reset_volatile() {

    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        pressed_keymap[i] = false;
        released_keymap[i] = false;
    }

    for (int i = 0; i < sf::Mouse::ButtonCount; ++i) {
        pressed_mousemap[i] = false;
        released_mousemap[i] = false;
    }

}

sge::core::InputManager::InputManager() :
    Subsystem("INPUT MANAGER"){
}

void sge::core::InputManager::print_keymaps() {
    printf("KEY DOWN: ");
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        printf("%d", down_keymap[i]);
    }
    printf("\n");

    printf("KEY PRSS: ");
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        printf("%d", pressed_keymap[i]);
    }
    printf("\n");

    printf("KEY RELS: ");
    for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
        printf("%d", released_keymap[i]);
    }
    printf("\n\n");
}

bool sge::core::InputManager::is_key_down(sf::Keyboard::Key key) {
    return down_keymap[(int) key];
}

bool sge::core::InputManager::is_key_pressed(sf::Keyboard::Key key) {
    return pressed_keymap[(int) key];
}

bool sge::core::InputManager::is_key_released(sf::Keyboard::Key key) {
    return released_keymap[(int) key];
}

bool sge::core::InputManager::is_mouse_down(sf::Mouse::Button button) {
    return down_mousemap[(int) button];
}

bool sge::core::InputManager::is_mouse_released(sf::Mouse::Button button) {
    return released_mousemap[(int) button];
}

bool sge::core::InputManager::is_mouse_pressed(sf::Mouse::Button button) {
    return pressed_mousemap[(int) button];
}

void sge::core::InputManager::print_mousemaps() {
    printf("MOUSE DOWN: ");
    for (int i = 0; i < sf::Mouse::ButtonCount; ++i) {
        printf("%d", down_mousemap[i]);
    }
    printf("\n");

    printf("MOUSE PRSS: ");
    for (int i = 0; i < sf::Mouse::ButtonCount; ++i) {
        printf("%d", pressed_mousemap[i]);
    }
    printf("\n");

    printf("MOUSE RELS: ");
    for (int i = 0; i < sf::Mouse::ButtonCount; ++i) {
        printf("%d", released_mousemap[i]);
    }
    printf("\n\n");
}

void sge::core::InputManager::pressed_key_callback(sf::Keyboard::Key key) {
    pressed_keymap[(int) key] = true;
    down_keymap[(int) key] = true;
}

void sge::core::InputManager::released_key_callback(sf::Keyboard::Key key) {
    released_keymap[(int) key] = true;
    down_keymap[(int) key] = false;
}

void sge::core::InputManager::pressed_mouse_callback(sf::Mouse::Button button) {
    pressed_mousemap[(int) button] = true;
    down_mousemap[(int) button] = true;
}

void sge::core::InputManager::released_mouse_callback(sf::Mouse::Button button) {
    released_mousemap[(int) button] = true;
    down_mousemap[(int) button] = false;
}

