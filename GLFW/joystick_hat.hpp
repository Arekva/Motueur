#pragma once

enum class JoystickHat : unsigned char {
	Centered =	GLFW_HAT_CENTERED,
	Up =		GLFW_HAT_UP,
	Right =		GLFW_HAT_RIGHT,
	Down =		GLFW_HAT_DOWN,
	Left =		GLFW_HAT_LEFT,
	RightUp =	GLFW_HAT_RIGHT_UP,
	RightDown = GLFW_HAT_RIGHT_DOWN,
	LeftUp =	GLFW_HAT_LEFT_UP,
	LeftDown =	GLFW_HAT_LEFT_DOWN,
};