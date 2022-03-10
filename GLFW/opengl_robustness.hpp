#pragma once

enum class OpenGLRobustness {
	None =					GLFW_NO_ROBUSTNESS,
	ResetNotification =		GLFW_NO_RESET_NOTIFICATION,
	LoseContextOnRelease =	GLFW_LOSE_CONTEXT_ON_RESET,
};