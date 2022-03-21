#include <iostream>

#include <GL/glew.h>

#include "glfw.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "keyboard.hpp"
#include "mesh.hpp"
#include "time.hpp"
#include "shader.hpp"
#include "material.hpp"


using namespace GLFW;
using namespace Motueur;

void init_imgui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}

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

bool startup(GLFW::WindowInstance** win_handle) {
    if(!init_glfw()) return false;

    GLFW::WindowInstance* internal_handle = new GLFW::WindowInstance(800,600,"Motueur");
    *win_handle = internal_handle;

    Window* window = internal_handle->GetAPI();

    window->MakeContextCurrent();

    // glew
    glewInit();

    init_imgui(reinterpret_cast<GLFWwindow*>(window));

    // engine
    Mesh::init();

    Keyboard::init(window);

    Time::init();

    return true;
}


void shutdown(GLFW::WindowInstance* win_handle) {
    delete win_handle;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    Mesh::terminate();

    GLFW::Terminate();
}

void run(GLFW::WindowInstance* win_handle) {
    Window* window = win_handle->GetAPI();
    GLFWwindow* glfw_win = reinterpret_cast<GLFWwindow*>(window);

    glViewport(0, 0, 800, 600);

    glClearColor(1.0F, 1.0F, 0.0F, 1.0F);

    bool should_close = false;

    bool someBoolean;
    float speed;

    {
        std::shared_ptr<Shader> shader = std::make_unique<Shader>(
                "C:/Users/Arthur/Documents/Code/Repos/cpp/Motueur/assets/shaders/standard");

        std::unique_ptr<Material> material = std::make_unique<Material>(shader);


    }

    while(!should_close) {
        GLFW::PollEvents();
        Keyboard::next_frame();
        Time::next_frame();

        if (Keyboard::is_pressing(Key::Escape) || window->ShouldClose())
        {
            should_close = true;
            continue; // on revient au début de la boucle pour qu'elle ce quitte proprement.
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("MyWindow");
        ImGui::Checkbox("Boolean property", &someBoolean);
        if(ImGui::Button("Reset Speed")) {
            // This code is executed when the user clicks the button
            speed = 0;
        }
        ImGui::SliderFloat("Speed", &speed, 0.0f, 10.0f);
        ImGui::End();

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        window->SwapBuffers();
    }
}

int main() {
    GLFW::WindowInstance* win_handle;
    if(!startup(&win_handle)) return -1;

    run(win_handle);

    shutdown(win_handle);

    return 0;
}