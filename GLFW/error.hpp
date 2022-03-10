#pragma once

enum class Error {
	None =					GLFW_NO_ERROR,
	NotInitialized =		GLFW_NOT_INITIALIZED,
	NoCurrentContext =		GLFW_NO_CURRENT_CONTEXT,
	InvalidEnum =			GLFW_INVALID_ENUM,
	InvalidValue =			GLFW_INVALID_VALUE,
	OutOfMemory =			GLFW_OUT_OF_MEMORY,
	APIUnavailable =		GLFW_API_UNAVAILABLE,
	VersionUnavailable =	GLFW_VERSION_UNAVAILABLE,
	PlatformError =			GLFW_PLATFORM_ERROR,
	FormatUnavailable =		GLFW_FORMAT_UNAVAILABLE,
	NoWindowContext =		GLFW_NO_WINDOW_CONTEXT,
};