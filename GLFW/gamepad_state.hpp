#pragma once

#include "input_action.hpp"

struct GamepadState {
	InputAction buttons[15];
	float axes[6];
};