//
// Created by Arthur on 11/03/2022.
//

#include "keyboard.hpp"
#include "glfw.hpp"

namespace Motueur {

void register_key_press(GLFW::Window* window, GLFW::Key key, int scancode, GLFW::InputAction action, GLFW::Mod mods) {
    if (action == GLFW::InputAction::Release) {
        Keyboard::pressed_keys[2].erase(key);
    } else {
        Keyboard::pressed_keys[2].insert(key);
    }
}

void Keyboard::init(GLFW::Window* window) {
    window->SetKeyCallback(register_key_press);

    // réserver 120 éléments (max nombre touches) pour éviter des réallocations par la suite
    for (int i = 0; i < 3; ++i) Keyboard::pressed_keys[i].reserve(120);

    Keyboard::current_frame_index = 0;
    Keyboard::previous_frame_index = 1;
}

void Keyboard::next_frame() {
    int current_frame_index = Keyboard::current_frame_index;
    int next_frame_index = (current_frame_index + 1) % 2;

    // clone recording keys in next frame storage
    Keyboard::pressed_keys[next_frame_index] = Keyboard::pressed_keys[2];

    Keyboard::current_frame_index = next_frame_index;
    Keyboard::previous_frame_index = current_frame_index;
}

inline bool Keyboard::is_any_pressed() {
    return Keyboard::pressed_keys[2].begin() != Keyboard::pressed_keys[2].end();
}

bool Keyboard::is_pressed(GLFW::Key key) {
    std::unordered_set<GLFW::Key>* set = &Keyboard::pressed_keys[Keyboard::current_frame_index];

    return set->find(key) != set->end();
}
bool Keyboard::is_released(GLFW::Key key) {
    std::unordered_set<GLFW::Key>* set = &Keyboard::pressed_keys[Keyboard::current_frame_index];

    return set->find(key) == set->end();
}

bool Keyboard::is_pressing(GLFW::Key key) {
    std::unordered_set<GLFW::Key>* frame_set = &Keyboard::pressed_keys[Keyboard::current_frame_index];
    std::unordered_set<GLFW::Key>* previous_set = &Keyboard::pressed_keys[Keyboard::previous_frame_index];

    return (frame_set->find(key) != frame_set->end()) && (previous_set->find(key) == previous_set->end());
}
bool Keyboard::is_releasing(GLFW::Key key) {
    std::unordered_set<GLFW::Key>* frame_set = &Keyboard::pressed_keys[Keyboard::current_frame_index];
    std::unordered_set<GLFW::Key>* previous_set = &Keyboard::pressed_keys[Keyboard::previous_frame_index];

    return (frame_set->find(key) == frame_set->end()) && (previous_set->find(key) != previous_set->end());
}

} // namespace Motueur