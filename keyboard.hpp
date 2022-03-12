//
// Created by Arthur on 11/03/2022.
//

#pragma once

#include <unordered_set>

namespace GLFW {
    class Window;
    enum class Key;
} // namespace GLFW

namespace Motueur {

namespace Keyboard {

    // [0] - touches appuyées pour la frame en cours
    // [1] - touches appuyées à la frame d'avant (calcul des IsPressing / IsReleasing)
    // [2] - touches en cours d'enregistrement pour la frame d'après
    static std::unordered_set<GLFW::Key> pressed_keys[3];
    static int previous_frame_index;
    static int current_frame_index;


    void init(GLFW::Window* window);
    void next_frame();

    bool is_any_pressed();

    bool is_pressed  (GLFW::Key key);
    bool is_released (GLFW::Key key);

    bool is_pressing (GLFW::Key key);
    bool is_releasing(GLFW::Key key);

} // namespace Input

} // namespace Motueur
