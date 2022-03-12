#include <iostream>

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "glfw.hpp"

#include "keyboard.hpp"

using namespace GLFW;
using namespace Motueur;

//namespace Motueur {

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

    glewInit();
    Keyboard::init(window);

    // window->SetInputMode(InputMode::StickyKeys, true);

    glViewport(0, 0, 800, 600);

    bool should_close = false;

    while(!should_close) {
        GLFW::PollEvents();
        Keyboard::next_frame();

        if (Keyboard::is_pressing(Key::Escape) || window->ShouldClose())
        {
            should_close = true;
            continue; // on revient au début de la boucle pour qu'elle ce quitte proprement.
        }

        glClearColor(1.0F, 1.0F, 0.0F, 1.0F);
        glClear(GL_COLOR_BUFFER_BIT);

        window->SwapBuffers();
    }

    GLFW::Terminate();

    return 0;
}

//} // namespace Motueur