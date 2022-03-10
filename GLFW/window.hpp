#pragma once

#include "image.hpp"

#include "input_mode.hpp"

#include "cursor.hpp"
#include "monitor.hpp"

#define CREATE(object) glfwCreate##object

#define DESTROY(object) glfwDestroy##object

#define SET(property) glfwSetWindow##property
#define SET_NO_WIN(property) glfwSet##property

#define GET(property) glfwGetWindow##property
#define GET_NO_GET(property) glfwWindow##property
#define GET_NO_WIN(property) glfwGet##property

#define DO(property) glfw##property##Window

#define RECAST(T, ptr) reinterpret_cast<T>(ptr)

#define N_THIS RECAST(GLFWwindow*, this)

class Window {
	typedef void (*PosFun)(Window* window, int xpos, int ypos);
	typedef void (*SizeFun)(Window* window, int width, int height);
	typedef void (*CloseFun)(Window* window);
	typedef void (*RefreshFun)(Window* window);
	typedef void (*FocusFun)(Window* window, bool focused);
	typedef void (*IconifyFun)(Window* window, bool iconified);
	typedef void (*MaximizeFun)(Window* window, bool maximized);
	typedef void (*FramebufferSizeFun)(Window* window, int width, int height);
	typedef void (*ContentScaleFun)(Window* window, float xscale, float yscale);
	typedef void (*MouseButtonFun)(Window* window, MouseButton button, InputAction action, Mod mods);
	typedef void (*CursorPosFun)(Window* window, double xpos, double ypos);
	typedef void (*CursorEnterFun)(Window* window, bool entered);
	typedef void (*ScrollFun)(Window* window, double xoffset, double yoffset);
	typedef void (*KeyFun)(Window* window, Key key, int scancode, InputAction action, Mod mods);
	typedef void (*CharFun)(Window* window, unsigned int codepoint);
	typedef void (*CharModsFun)(Window* window, unsigned int codepoint, Mod mods);
	typedef void (*DropFun)(Window* window, int path_count, const char* paths[]);
public:
bool ShouldClose()
{
	return GET_NO_GET(ShouldClose)(N_THIS);
}

void SetShouldClose(bool value)
{
	SET(ShouldClose)(N_THIS, value);
}

void SetTitle(const char* title)
{
	SET(Title)(N_THIS, title);
}

void SetIcon(int count, 
			 const Image* images)
{
	SET(Icon)(N_THIS, count, RECAST(const GLFWimage*, images));
}

void GetPos(int* xpos, int* ypos)
{
	GET(Pos)(N_THIS, xpos, ypos);
}

void SetPos(int xpos, int ypos)
{
	SET(Pos)(N_THIS, xpos, ypos);
}

void GetSize(int* width, int* height)
{
	GET(Size)(N_THIS, width, height);
}

void SetSizeLimits(int minwidth, int minheight, 
				   int maxwidth, int maxheight)
{
	SET(SizeLimits)(N_THIS, minwidth, minheight, maxwidth, maxheight);
}

void SetAspectRatio(int numer, int denom)
{
	SET(AspectRatio)(N_THIS, numer, denom);
}

void SetSize(int width, int height)
{
	SET(Size)(N_THIS, width, height);
}

void GetFramebufferSize(int* width, int* height)
{
	GET_NO_WIN(FramebufferSize)(N_THIS, width, height);
}

void GetFrameSize(int* left, int* top, int* right, int* bottom)
{
	GET(FrameSize)(N_THIS, left, top, right, bottom);
}

void GetContentScale(float* xscale, float* yscale)
{
	GET(ContentScale)(N_THIS, xscale, yscale);
}

float GetOpacity()
{
	return GET(Opacity)(N_THIS);
}

void SetOpacity(float opacity)
{
	SET(Opacity)(N_THIS, opacity);
}

void Iconify()
{
	DO(Iconify)(N_THIS);
}

void Restore()
{
	DO(Restore)(N_THIS);
}

void Maximize()
{
	DO(Maximize)(N_THIS);
}

void Show()
{
	DO(Show)(N_THIS);
}

void Hide()
{
	DO(Hide)(N_THIS);
}

void Focus()
{
	DO(Focus)(N_THIS);
}

void RequestAttention()
{
	glfwRequestWindowAttention(N_THIS);
}

Monitor* GetMonitor()
{
	return RECAST(Monitor*, GET(Monitor)(N_THIS));
}

void SetMonitor(Monitor* monitor,
				int xpos, int ypos, 
				int width, int height, 
				int refreshRate)
{
	SET(Monitor)(N_THIS, RECAST(GLFWmonitor*, monitor), xpos, ypos, width, height, refreshRate);
}

bool GetAttrib(int attrib)
{
	return GET(Attrib)(N_THIS, attrib);
}

void SetAttrib(int attrib, bool value)
{
	SET(Attrib)(N_THIS, attrib, value);
}

void SetUserPointer(void* pointer)
{
	SET(UserPointer)(N_THIS, pointer);
}

void* GetUserPointer()
{
	return GET(UserPointer)(N_THIS);
}

PosFun SetPosCallback(PosFun callback)
{
	return RECAST(PosFun, SET(PosCallback)(N_THIS, RECAST(GLFWwindowposfun, callback)));
}

SizeFun SetSizeCallback(SizeFun callback)
{
	return RECAST(SizeFun, SET(SizeCallback)(N_THIS, RECAST(GLFWwindowsizefun, callback)));
}

CloseFun SetCloseCallback(CloseFun callback)
{
	return RECAST(CloseFun, SET(CloseCallback)(N_THIS, RECAST(GLFWwindowclosefun, callback)));
}

RefreshFun SetRefreshCallback(RefreshFun callback)
{
	return RECAST(RefreshFun, SET(RefreshCallback)(N_THIS, RECAST(GLFWwindowrefreshfun, callback)));
}

FocusFun SetFocusCallback(FocusFun callback)
{
	return RECAST(FocusFun, SET(FocusCallback)(N_THIS, RECAST(GLFWwindowfocusfun, callback)));
}

IconifyFun SetIconifyCallback(IconifyFun callback)
{
	return RECAST(IconifyFun, SET(FocusCallback)(N_THIS, RECAST(GLFWwindowiconifyfun, callback)));
}

MaximizeFun SetMaximizeCallback(MaximizeFun callback)
{
	return RECAST(MaximizeFun, SET(FocusCallback)(N_THIS, RECAST(GLFWwindowmaximizefun, callback)));
}

FramebufferSizeFun SetFramebufferSizeCallback(FramebufferSizeFun callback)
{
	return RECAST(FramebufferSizeFun, SET_NO_WIN(FramebufferSizeCallback)(N_THIS, RECAST(GLFWframebuffersizefun, callback)));
}

ContentScaleFun SetContentCallback(ContentScaleFun callback)
{
	return RECAST(ContentScaleFun, SET(ContentScaleCallback)(N_THIS, RECAST(GLFWwindowcontentscalefun, callback)));
}


bool GetInputMode(InputMode mode)
{
	return GET_NO_WIN(InputMode)(N_THIS, static_cast<int>(mode));
}

void SetInputMode(InputMode mode, bool value)
{
	SET_NO_WIN(InputMode)(N_THIS, static_cast<int>(mode), value);
}

InputAction GetKey(Key key)
{
	return static_cast<InputAction>(GET_NO_WIN(Key)(N_THIS, static_cast<int>(key)));
}

InputAction GetMouseButton(MouseButton button)
{
	return static_cast<InputAction>(GET_NO_WIN(MouseButton)(N_THIS, static_cast<int>(button)));
}

void GetCursorPos(double* xpos, double* ypos)
{
	GET_NO_WIN(CursorPos)(N_THIS, xpos, ypos);
}

void SetCursorPos(double xpos, double ypos)
{
	SET_NO_WIN(CursorPos)(N_THIS, xpos, ypos);
}

void SetCursor(Cursor* cursor)
{
	SET_NO_WIN(Cursor)(N_THIS, RECAST(GLFWcursor*, cursor));
}

KeyFun SetKeyCallback(KeyFun callback)
{
	return RECAST(KeyFun, SET_NO_WIN(KeyCallback)(N_THIS, RECAST(GLFWkeyfun, callback)));
}

CharFun SetCharCallback(CharFun callback)
{
	return RECAST(CharFun, SET_NO_WIN(CharCallback)(N_THIS, RECAST(GLFWcharfun, callback)));
}

CharModsFun SetCharModsCallback(CharModsFun callback)
{
	return RECAST(CharModsFun, SET_NO_WIN(CharModsCallback)(N_THIS, RECAST(GLFWcharmodsfun, callback)));
}

MouseButtonFun SetMouseButtonCallback(MouseButtonFun callback)
{
	return RECAST(MouseButtonFun, SET_NO_WIN(MouseButtonCallback)(N_THIS, RECAST(GLFWmousebuttonfun, callback)));
}

CursorPosFun SetCursorPosCallback(CursorPosFun callback)
{
	return RECAST(CursorPosFun, SET_NO_WIN(CursorPosCallback)(N_THIS, RECAST(GLFWcursorposfun, callback)));
}

CursorEnterFun SetCursorEnterCallback(CursorEnterFun callback)
{
	return RECAST(CursorEnterFun, SET_NO_WIN(CursorEnterCallback)(N_THIS, RECAST(GLFWcursorenterfun, callback)));
}

ScrollFun SetScrollCallback(ScrollFun callback)
{
	return RECAST(ScrollFun, SET_NO_WIN(ScrollCallback)(N_THIS, RECAST(GLFWscrollfun, callback)));
}

DropFun SetDropCallback(DropFun callback)
{
	return RECAST(DropFun, SET_NO_WIN(DropCallback)(N_THIS, RECAST(GLFWdropfun, callback)));
}

void SetClipboardString(const char* string)
{
	SET_NO_WIN(ClipboardString)(N_THIS, string);
}

const char* GetClipboardString()
{
	return GET_NO_WIN(ClipboardString)(N_THIS);
}

void MakeContextCurrent()
{
	glfwMakeContextCurrent(N_THIS);
}

void SwapBuffers()
{
	glfwSwapBuffers(N_THIS);
}

};

class WindowInstance : Window {
private:
	Window* window;
public:
WindowInstance(int width, int height, 
			   const char* title, 
			   Monitor* monitor, Window* context)
{
	this->window = RECAST(Window*, CREATE(Window)(width, height, title, RECAST(GLFWmonitor*, monitor), RECAST(GLFWwindow*, context)));
}

~WindowInstance()
{
	DESTROY(Window)(RECAST(GLFWwindow*, this->window));
}

/* API EXTENSIONS */
Window* GetAPI()
{
	return window;
}

WindowInstance(int width, int height,
	           const char* title) : WindowInstance(width, height, title, nullptr, nullptr) 
{

}

};

#undef CREATE
#undef DESTROY
#undef SET
#undef SET_NO_WIN
#undef GET
#undef GET_NO_GET
#undef GET_NO_WIN
#undef DO
#undef N_THIS
#undef RECAST