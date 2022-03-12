#pragma once

#include <GLFW/glfw3.h>

namespace GLFW {

// enums
#include "GLFW/device_event.hpp"
#include "GLFW/context_api.hpp"
#include "GLFW/cursor_icon.hpp"
#include "GLFW/cursor_mode.hpp"
#include "GLFW/opengl_api.hpp"
#include "GLFW/attribute.hpp"
#include "GLFW/error.hpp"
#include "GLFW/gamepad_axis.hpp"
#include "GLFW/joystick_hat.hpp"
#include "GLFW/hint.hpp"
#include "GLFW/input_action.hpp"
#include "GLFW/gamepad_button.hpp"
#include "GLFW/input_mode.hpp"
#include "GLFW/joystick_button.hpp"
#include "GLFW/key.hpp"
#include "GLFW/mod.hpp"
#include "GLFW/mouse_button.hpp"
#include "GLFW/opengl_profile.hpp"
#include "GLFW/opengl_robustness.hpp"
#include "GLFW/release_behavior.hpp"

// structs
#include "GLFW/gamepad_state.hpp"
#include "GLFW/gamma_ramp.hpp"
#include "GLFW/image.hpp"
#include "GLFW/video_mode.hpp"

// objects
#include "GLFW/cursor.hpp"
#include "GLFW/monitor.hpp"
#include "GLFW/window.hpp"

typedef GLFWglproc GLProc;

#if defined(VK_VERSION_1_0)
	typedef GLFWvkproc VKProc;
#endif

typedef void (*ErrorFun)(Error error_code, const char* description);

typedef void (*MonitorFunc)(Monitor* monitor, DeviceEvent event);

typedef void (*JoystickFun)(int jid, DeviceEvent event);


inline static bool Init()
{
	return glfwInit();
}

inline static void Terminate()
{
	glfwTerminate();
}

inline static void InitHint(int hint, int value)
{
	glfwInitHint(hint, value);
}
inline static void GetVersion(int* major, int* minor, int* rev)
{
	return glfwGetVersion(major, minor, rev);
}

inline static const char* GetVersionString()
{
	return glfwGetVersionString();
}

inline static Error GetError(const char** description)
{
	return static_cast<Error>(glfwGetError(description));
}

inline static ErrorFun SetErrorCallback(ErrorFun callback)
{
	return reinterpret_cast<ErrorFun>(glfwSetErrorCallback(reinterpret_cast<GLFWerrorfun>(callback)));
}

inline static Monitor** GetMonitors(int* count)
{
	return reinterpret_cast<Monitor**>(glfwGetMonitors(count));
}

inline static Monitor* GetPrimaryMonitor()
{
	return reinterpret_cast<Monitor*>(glfwGetPrimaryMonitor());
}

inline static MonitorFunc SetMonitorCallback(MonitorFunc callback)
{
	return reinterpret_cast<MonitorFunc>(glfwSetMonitorCallback(reinterpret_cast<GLFWmonitorfun>(callback)));
}

inline static void DefaultWindowHints()
{
	glfwDefaultWindowHints();
}

// moved at GLFW::WindowHint::Generic(int,int)
/*void WindowHint(int hint, int value) {
	glfwWindowHint(hint, value);
}*/

inline static void WindowHintString(int hint, const char* value)
{
	glfwWindowHintString(hint, value);
}

inline static void PollEvents()
{
	glfwPollEvents();
}

inline static void WaitEvents()
{
	glfwWaitEvents();
}

inline static void WaitEventsTimeout(double timeout)
{
	glfwWaitEventsTimeout(timeout);
}

inline static void PostEmptyEvent()
{
	glfwPostEmptyEvent();
}

inline static bool RawMouseMotionSupported()
{
	return glfwRawMouseMotionSupported();
}

inline static const char* GetKeyName(Key key, int scancode)
{
	return glfwGetKeyName(static_cast<int>(key), scancode);
}

inline static int GetKeyScancode(Key key)
{
	return glfwGetKeyScancode(static_cast<int>(key));
}

inline static bool JoystickPresent(int jid)
{
	return glfwJoystickPresent(jid);
}

inline static const float* GetJoystickAxes(int jid, int* count)
{
	return glfwGetJoystickAxes(jid, count);
}

inline static const JoystickButton* GetJoystickButtons(int jid, int* count)
{
	return reinterpret_cast<const JoystickButton*>(glfwGetJoystickButtons(jid, count));
}

inline static const JoystickHat* GetJoystickHats(int jid, int* count)
{
	return reinterpret_cast<const JoystickHat*>(glfwGetJoystickHats(jid, count));
}

inline static const char* GetJoystickName(int jid)
{
	return glfwGetJoystickName(jid);
}

inline static const char* GetJoystickGUID(int jid)
{
	return glfwGetJoystickGUID(jid);
}

inline static void SetJoystickUserPointer(int jid, void* pointer)
{
	glfwSetJoystickUserPointer(jid, pointer);
}

inline static void* GetJoystickUserPointer(int jid)
{
	return glfwGetJoystickUserPointer(jid);
}

inline static bool JoystickIsGamepad(int jid)
{
	return glfwJoystickIsGamepad(jid);
}

inline static JoystickFun SetJoystickCallback(JoystickFun callback)
{
	return reinterpret_cast<JoystickFun>(glfwSetJoystickCallback(reinterpret_cast<GLFWjoystickfun>(callback)));
}

inline static bool UpdateGamepadMappings(const char* string)
{
	return glfwUpdateGamepadMappings(string);
}

inline static const char* GetGamepadName(int jid)
{
	return glfwGetGamepadName(jid);
}

inline static bool GetGamepadState(int jid, GamepadState* state)
{
	return glfwGetGamepadState(jid, reinterpret_cast<GLFWgamepadstate*>(state));
}

inline static double GetTime()
{
	return glfwGetTime();
}

inline static void SetTime(double time)
{
	glfwSetTime(time);
}

inline uint64_t GetTimerValue()
{
	return glfwGetTimerValue();
}

inline static uint64_t GetTimerFrequency()
{
	return glfwGetTimerFrequency();
}

inline static Window* GetCurrentContext()
{
	return reinterpret_cast<Window*>(glfwGetCurrentContext());
}

inline static void SwapInterval(int interval)
{
	glfwSwapInterval(interval);
}

inline static bool ExtensionSupported(const char* extension)
{
	return glfwExtensionSupported(extension);
}

inline static GLProc GetProcAddress(const char* procname)
{
	return reinterpret_cast<GLProc>(glfwGetProcAddress(procname));
}

inline static bool VulkanSupported()
{
	return glfwVulkanSupported();
}

inline static const char** GetRequiredInstanceExtensions(uint32_t* count)
{
	return glfwGetRequiredInstanceExtensions(count);
}

#if defined(VK_VERSION_1_0)
    inline VKProc GetInstanceProcAddress(VkInstance instance, const char* procname)
	{
		return reinterpret_cast<VKProc>(glfwGetInstanceProcAddress(instance, procname));
	}

	inline bool GetPhysicalDevicePresentationSupport(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily)
	{
		return glfwGetPhysicalDevicePresentationSupport(instance, device, queuefamily);
	}

	inline VkResult CreateWindowSurface(VkInstance instance, Window* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
	{
		return glfwCreateWindowSurface(instance, reinterpret_cast<GLFWwindow*>(window), allocator, surface);
	}
#endif

/* API EXTENSIONS */

namespace WindowHint {
#define CAST(value) static_cast<int>(value)

inline static void Generic(int hint, int value)
{
	glfwWindowHint(hint, value);
}

inline static void ClientAPI(GLFW::OpenGLAPI api)
{
	Generic(CAST(GLFW::Hint::ClientAPI), CAST(api));
}

inline static void ContextVersionMajor(int major)
{
    Generic(CAST(GLFW::Hint::ContextVersionMajor), major);
}

inline static void ContextVersionMinor(int minor)
{
    Generic(CAST(GLFW::Hint::ContextVersionMinor), minor);
}

inline static void OpenGLForwardCompat(bool value)
{
    Generic(CAST(GLFW::Hint::OpenGLForwardCompat), value);
}

inline static void OpenGLProfile(GLFW::OpenGLProfile profile)
{
    Generic(CAST(GLFW::Hint::OpenGLProfile), CAST(profile));
}

#undef CAST
} /* namespace GLFW::WindowHint */

} /* namespace GLFW */

