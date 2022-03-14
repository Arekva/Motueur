#include <iostream>

#include <GL/glew.h>

#include "glfw.hpp"

#include "keyboard.hpp"
#include "mesh.hpp"


using namespace GLFW;
using namespace Motueur;

bool init_glfw() {
    if (!GLFW::Init()){
        std::cout << "Failed to init GLFW." << std::endl;
        return false;
    }

    // OpenGL 4.5
    GLFW::WindowHint::ClientAPI(GLFW::OpenGLAPI::OpenGL);
    GLFW::WindowHint::ContextVersionMajor(4);
    GLFW::WindowHint::ContextVersionMinor(5);

    // MacOS
    GLFW::WindowHint::OpenGLForwardCompat(true);
    GLFW::WindowHint::OpenGLProfile(GLFW::OpenGLProfile::Core);

    return true;
}

bool startup() {
    // glfw
    if(!init_glfw()) return false;

    // glew
    glewInit();

    // engine
    Mesh::init();

    return true;
}

void shutdown() {
    Mesh::terminate();

    GLFW::Terminate();
}

void run() {
    auto win_handle = std::make_unique<GLFW::WindowInstance>(
        800,
        600,
        "Atom"
    );

    Window* window = win_handle->GetAPI();

    window->MakeContextCurrent();

    Keyboard::init(window);

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
}

int main() {
    if(!startup()) return -1;

    run();

    shutdown();

    return 0;
}