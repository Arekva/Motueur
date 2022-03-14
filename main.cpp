#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>

#include <GL/glew.h>

#include "glfw.hpp"
#include "keyboard.hpp"
#include "mesh.hpp"
#include "camera.hpp"


using namespace GLFW;
using namespace Motueur;

int width = 800;
int heigth = 600;

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





    return true;
}

void shutdown() {
    Mesh::terminate();

    GLFW::Terminate();
}

void run() {
    auto win_handle = std::make_unique<GLFW::WindowInstance>(
        width,
        heigth,
        "Atom"
    );
    camera c;

    c.position = glm::vec3(0, 0, 0);
    c.horizontalRot = 3.14f;
    c.verticalRot = 0.0;
    c.direction = glm::vec3(cos(c.verticalRot) * sin(c.horizontalRot), sin(c.verticalRot), cos(c.verticalRot) * cos(c.horizontalRot));
    c.right = glm::vec3(sin(c.verticalRot - M_PI / 2.0f), 0.0f, cos(c.verticalRot - M_PI / 2.0f));
    c.up = glm::cross(c.right, c.direction);

    Window* window = win_handle->GetAPI();

    window->MakeContextCurrent();

    // glew
    glewInit();

    // engine
    Mesh::init();

    Keyboard::init(window);

    glViewport(0, 0, 800, 600);

    bool should_close = false;

    while(!should_close) {
        GLFW::PollEvents();
        Keyboard::next_frame();

        if(Keyboard::is_pressing(Key::Z))
        {
        }
        if (Keyboard::is_pressing(Key::Escape) || window->ShouldClose())
        {
            should_close = true;
            continue; // on revient au début de la boucle pour qu'elle ce quitte proprement.
        }
        if (true);

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