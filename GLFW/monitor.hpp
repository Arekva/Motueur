#pragma once

#include "video_mode.hpp"
#include "gamma_ramp.hpp"

#define N_THIS reinterpret_cast<GLFWmonitor*>(this)

#define SET(property) glfwSetMonitor##property
#define SET_NO_MON(property) glfwSet##property

#define GET(property) glfwGetMonitor##property
#define GET_NO_GET(property) glfwMonitor##property
#define GET_NO_MON(property) glfwGet##property

#define DO(property) glfw##property##Window

class Monitor {

public:
void GetPos(int* xpos, int* ypos)
{
	GET(Pos)(N_THIS, xpos, ypos);
}

void GetWorkarea(int* xpos, int* ypos, int* width, int* height)
{
	GET(Workarea)(N_THIS, xpos, ypos, width, height);
}

void GetPhysicalSize(int* widthMM, int* heightMM)
{
	GET(PhysicalSize)(N_THIS, widthMM, heightMM);
}

void GetContentScale(float* xscale, float* yscale)
{
	GET(ContentScale)(N_THIS, xscale, yscale);
}

const char* GetName()
{
	return glfwGetMonitorName(N_THIS);
}

void SetUserPointer(void* pointer)
{
	SET(UserPointer)(N_THIS, pointer);
}

void* GetUserPointer()
{
	return GET(UserPointer)(N_THIS);
}

const VideoMode* GetVideoModes(int* count)
{
	return reinterpret_cast<const VideoMode*>(GET_NO_MON(VideoModes)(N_THIS, count));
}

const VideoMode* GetVideoMode()
{
	return reinterpret_cast<const VideoMode*>(GET_NO_MON(VideoMode)(N_THIS));
}

void SetGamma(float gamma)
{
	SET_NO_MON(Gamma)(N_THIS, gamma);
}

const GammaRamp* GetGammaRamp()
{
	return reinterpret_cast<const GammaRamp*>(GET_NO_MON(GammaRamp)(N_THIS));
}

void SetGammaRamp(const GammaRamp* ramp)
{
	SET_NO_MON(GammaRamp)(N_THIS, reinterpret_cast<const GLFWgammaramp*>(ramp));
}

};

#undef SET
#undef GET
#undef GET_NO_GET
#undef GET_NO_MON
#undef DO

#undef N_THIS
