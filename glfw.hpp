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


bool Init()
{
	return glfwInit();
}

void Terminate()
{
	glfwTerminate();
}

void InitHint(int hint, int value)
{
	glfwInitHint(hint, value);
}

void GetVersion(int* major, int* minor, int* rev)
{
	return glfwGetVersion(major, minor, rev);
}

const char* GetVersionString()
{
	return glfwGetVersionString();
}

Error GetError(const char** description)
{
	return static_cast<Error>(glfwGetError(description));
}

ErrorFun SetErrorCallback(ErrorFun callback) 
{
	return reinterpret_cast<ErrorFun>(glfwSetErrorCallback(reinterpret_cast<GLFWerrorfun>(callback)));
}

Monitor** GetMonitors(int* count)
{
	return reinterpret_cast<Monitor**>(glfwGetMonitors(count));
}

Monitor* GetPrimaryMonitor() {
	return reinterpret_cast<Monitor*>(glfwGetPrimaryMonitor());
}

MonitorFunc SetMonitorCallback(MonitorFunc callback)
{
	return reinterpret_cast<MonitorFunc>(glfwSetMonitorCallback(reinterpret_cast<GLFWmonitorfun>(callback)));
}

void DefaultWindowHints()
{
	glfwDefaultWindowHints();
}

// moved at GLFW::WindowHint::Generic(int,int)
/*void WindowHint(int hint, int value) {
	glfwWindowHint(hint, value);
}*/

void WindowHintString(int hint, const char* value)
{
	glfwWindowHintString(hint, value);
}

void PollEvents()
{
	glfwPollEvents();
}

void WaitEvents()
{
	glfwWaitEvents();
}

void WaitEventsTimeout(double timeout)
{
	glfwWaitEventsTimeout(timeout);
}

void PostEmptyEvent()
{
	glfwPostEmptyEvent();
}

bool RawMouseMotionSupported()
{
	return glfwRawMouseMotionSupported();
}

const char* GetKeyName(Key key, int scancode)
{
	return glfwGetKeyName(static_cast<int>(key), scancode);
}

int GetKeyScancode(Key key)
{
	return glfwGetKeyScancode(static_cast<int>(key));
}

bool JoystickPresent(int jid)
{
	return glfwJoystickPresent(jid);
}

const float* GetJoystickAxes(int jid, int* count)
{
	return glfwGetJoystickAxes(jid, count);
}

const JoystickButton* GetJoystickButtons(int jid, int* count)
{
	return reinterpret_cast<const JoystickButton*>(glfwGetJoystickButtons(jid, count));
}

const JoystickHat* GetJoystickHats(int jid, int* count)
{
	return reinterpret_cast<const JoystickHat*>(glfwGetJoystickHats(jid, count));
}

const char* GetJoystickName(int jid)
{
	return glfwGetJoystickName(jid);
}

const char* GetJoystickGUID(int jid)
{
	return glfwGetJoystickGUID(jid);
}

void SetJoystickUserPointer(int jid, void* pointer)
{
	glfwSetJoystickUserPointer(jid, pointer);
}

void* GetJoystickUserPointer(int jid)
{
	return glfwGetJoystickUserPointer(jid);
}

bool JoystickIsGamepad(int jid)
{
	return glfwJoystickIsGamepad(jid);
}

JoystickFun SetJoystickCallback(JoystickFun callback)
{
	return reinterpret_cast<JoystickFun>(glfwSetJoystickCallback(reinterpret_cast<GLFWjoystickfun>(callback)));
}

bool UpdateGamepadMappings(const char* string)
{
	return glfwUpdateGamepadMappings(string);
}

const char* GetGamepadName(int jid)
{
	return glfwGetGamepadName(jid);
}

bool GetGamepadState(int jid, GamepadState* state)
{
	return glfwGetGamepadState(jid, reinterpret_cast<GLFWgamepadstate*>(state));
}

double GetTime()
{
	return glfwGetTime();
}

void SetTime(double time)
{
	glfwSetTime(time);
}

uint64_t GetTimerValue()
{
	return glfwGetTimerValue();
}

uint64_t GetTimerFrequency()
{
	return glfwGetTimerFrequency();
}

Window* GetCurrentContext()
{
	return reinterpret_cast<Window*>(glfwGetCurrentContext());
}

void SwapInterval(int interval)
{
	glfwSwapInterval(interval);
}

bool ExtensionSupported(const char* extension)
{
	return glfwExtensionSupported(extension);
}

GLProc GetProcAddress(const char* procname)
{
	return reinterpret_cast<GLProc>(glfwGetProcAddress(procname));
}

bool VulkanSupported()
{
	return glfwVulkanSupported();
}

const char** GetRequiredInstanceExtensions(uint32_t* count)
{
	return glfwGetRequiredInstanceExtensions(count);
}

#if defined(VK_VERSION_1_0)
	VKProc GetInstanceProcAddress(VkInstance instance, const char* procname)
	{
		return reinterpret_cast<VKProc>(glfwGetInstanceProcAddress(instance, procname));
	}

	bool GetPhysicalDevicePresentationSupport(VkInstance instance, VkPhysicalDevice device, uint32_t queuefamily)
	{
		return glfwGetPhysicalDevicePresentationSupport(instance, device, queuefamily);
	}

	VkResult CreateWindowSurface(VkInstance instance, Window* window, const VkAllocationCallbacks* allocator, VkSurfaceKHR* surface)
	{
		return glfwCreateWindowSurface(instance, reinterpret_cast<GLFWwindow*>(window), allocator, surface);
	}
#endif

/* API EXTENSIONS */

namespace WindowHint {
#define CAST(value) static_cast<int>(value)

void Generic(int hint, int value)
{
	glfwWindowHint(hint, value);
}

void ClientAPI(GLFW::OpenGLAPI api)
{
	Generic(CAST(GLFW::Hint::ClientAPI), CAST(api));
}

void ContextVersionMajor(int major)
{
    Generic(CAST(GLFW::Hint::ContextVersionMajor), major);
}

void ContextVersionMinor(int minor)
{
    Generic(CAST(GLFW::Hint::ContextVersionMinor), minor);
}

void OpenGLForwardCompat(bool value)
{
    Generic(CAST(GLFW::Hint::OpenGLForwardCompat), value);
}

void OpenGLProfile(GLFW::OpenGLProfile profile)
{
    Generic(CAST(GLFW::Hint::OpenGLProfile), CAST(profile));
}

#undef CAST
} /* namespace GLFW::WindowHint */

} /* namespace GLFW */

