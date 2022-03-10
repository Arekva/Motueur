#include <iostream>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "glfw.hpp"


using namespace GLFW;

int main() {

    if(!GLFW::Init())
    {
        std::cout << "Failed to init GLFW\n" << std::endl;
        return -1;
    }

    // OpenGL 4.5
    GLFW::WindowHint::ClientAPI(GLFW::OpenGLAPI::OpenGL);
    GLFW::WindowHint::ContextVersionMajor(4);
    GLFW::WindowHint::ContextVersionMinor(5);

    // MacOS
    GLFW::WindowHint::OpenGLForwardCompat(true);
    GLFW::WindowHint::OpenGLProfile(GLFW::OpenGLProfile::Core);

    auto win_handle = std::make_unique<GLFW::WindowInstance>(
        800,
        600,
        "Atom"
    );

    Window* window = win_handle->GetAPI();

    window->MakeContextCurrent();

    // window->SetInputMode(InputMode::StickyKeys, true);

    while(window->GetKey(GLFW::Key::Escape) != InputAction::Press && !window->ShouldClose()) {
        GLFW::PollEvents();

        window->SwapBuffers();
    }

    GLFW::Terminate();

    return 0;
}
