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
inline void GetPos(int* xpos, int* ypos)
{
	GET(Pos)(N_THIS, xpos, ypos);
}

inline void GetWorkarea(int* xpos, int* ypos, int* width, int* height)
{
	GET(Workarea)(N_THIS, xpos, ypos, width, height);
}

inline void GetPhysicalSize(int* widthMM, int* heightMM)
{
	GET(PhysicalSize)(N_THIS, widthMM, heightMM);
}

inline void GetContentScale(float* xscale, float* yscale)
{
	GET(ContentScale)(N_THIS, xscale, yscale);
}

inline const char* GetName()
{
	return glfwGetMonitorName(N_THIS);
}

inline void SetUserPointer(void* pointer)
{
	SET(UserPointer)(N_THIS, pointer);
}

inline void* GetUserPointer()
{
	return GET(UserPointer)(N_THIS);
}

inline const VideoMode* GetVideoModes(int* count)
{
	return reinterpret_cast<const VideoMode*>(GET_NO_MON(VideoModes)(N_THIS, count));
}

inline const VideoMode* GetVideoMode()
{
	return reinterpret_cast<const VideoMode*>(GET_NO_MON(VideoMode)(N_THIS));
}

inline void SetGamma(float gamma)
{
	SET_NO_MON(Gamma)(N_THIS, gamma);
}

inline const GammaRamp* GetGammaRamp()
{
	return reinterpret_cast<const GammaRamp*>(GET_NO_MON(GammaRamp)(N_THIS));
}

inline void SetGammaRamp(const GammaRamp* ramp)
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
