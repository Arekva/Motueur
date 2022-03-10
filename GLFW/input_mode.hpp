#pragma once

enum class InputMode {
	Cursor =				GLFW_CURSOR,
	StickyKeys =			GLFW_STICKY_KEYS,
	StickyMouseButtons =	GLFW_STICKY_MOUSE_BUTTONS,
	LockKeyMods =			GLFW_LOCK_KEY_MODS,
	RawMouseMotion =		GLFW_RAW_MOUSE_MOTION,
};