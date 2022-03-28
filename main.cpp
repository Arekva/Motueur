#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#endif

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/rotate_vector.hpp >

#include "glfw.hpp"
#include "keyboard.hpp"
#include "mesh.hpp"
#include "camera.hpp"
#include "time.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "material.hpp"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Model.hpp"

using namespace GLFW;
using namespace Motueur;




void init_imgui(GLFWwindow* window) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
}
int width = 800;
int height = 600;
float movespeed = 10.0f;
float mousespeed = 0.1f;
const float ratio = (float)width / height;
double posy, posx;
float lightX = 0.0, lightY = 2.0, lightZ = 5.0;
bool mouseActive;

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
    LoadModel m;
    camera c;
    Window* window = win_handle->GetAPI();
    GLFWwindow* glfw_win = reinterpret_cast<GLFWwindow*>(window);

    window->MakeContextCurrent();
    window->GetCursorPos(& posx, & posy);

    glfwSetInputMode(glfw_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mouseActive = false;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // glew
    glewInit();

    glClearColor(1.0F, 1.0F, 0.0F, 1.0F);

    //models 3D
std:vector<unsigned short> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normalsobj; // Won't be used at the moment.
    bool res = m.loadModel("assets\\models\\Echelle.fbx", indices, vertices, uvs, normalsobj);

    static const GLfloat g_vertex_buffer_data[] = {
        // up
        -1.0,  1.0, -1.0,
        -1.0,  1.0,  1.0,
         1.0,  1.0, -1.0,
         1.0,  1.0, -1.0,
        -1.0,  1.0,  1.0,
         1.0,  1.0,  1.0,

        //down
        -1.0, -1.0,  1.0,
        -1.0, -1.0, -1.0,
         1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,

        //west
        -1.0, -1.0, -1.0,
        -1.0, -1.0,  1.0,
        -1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
        -1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,

        //east
         1.0,  1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0, -1.0,
         1.0,  1.0, -1.0,
         1.0, -1.0,  1.0,
         1.0, -1.0, -1.0,

        //north
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
        -1.0,  1.0,  1.0,
         1.0, -1.0,  1.0,
         1.0,  1.0,  1.0,

        //south
         1.0,  1.0, -1.0,
         1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
        -1.0,  1.0, -1.0,
         1.0, -1.0, -1.0,
        -1.0, -1.0, -1.0,

    };

    static const GLfloat normals[] =
    {
        0,1,0,
        0,1,0,
        0,1,0,
        0,1,0,
        0,1,0,
        0,1,0,

        0,-1,0,
        0,-1,0,
        0,-1,0,
        0,-1,0,
        0,-1,0,
        0,-1,0,

        -1,0,0,
        -1,0,0,
        -1,0,0,
        -1,0,0,
        -1,0,0,
        -1,0,0,

        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,
        1,0,0,

        0,0,1,
        0,0,1,
        0,0,1,
        0,0,1,
        0,0,1,
        0,0,1,

        0,0,-1,
        0,0,-1,
        0,0,-1,
        0,0,-1,
        0,0,-1,
        0,0,-1
    };

    static const GLfloat g_uv_buffer_data[] = 
    {
        0.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,

        0.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,

        0.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,

        0.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,

        0.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,

        0.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,

    };

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normalsobj.size()*sizeof(glm::vec3), &normalsobj[0], GL_STATIC_DRAW);

    GLuint indicesbuffer;
    glGenBuffers(1, &indicesbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

    std::shared_ptr<Shader> shader = std::make_unique<Shader>("assets/shaders/thomas");

    glViewport(0, 0, width, height);

    c.position = glm::vec3(lightX, lightY, lightZ);
    c.up = glm::vec3(0, 1, 0);

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 10000.0f);

    glm::mat4 View = glm::lookAt(
        c.position,
        glm::vec3(0, 0, 0), // and looks at the origin
        c.up
    );

    glm::vec3 Light = { 0,2,5 };
    glm::vec4 LightColor = { 1,1,1,150};
    
    glm::mat4 camTransform = glm::inverse(View);
    c.right = camTransform[0];
    c.up = camTransform[1];
    c.front = camTransform[2];
    

    Texture t("assets/textures/test.png");

    std::unique_ptr<Material> material = std::make_unique<Material>(shader);
    material->set_data("myTextureSampler", &t);

    bool someBoolean;
    float speed;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    window->SetSizeCallback([] (Window* win, int w, int h) {
        width  = w;
        height = h;
        glViewport(0.0F, 0.0F, width, height);
    });

    bool should_close = false;
    while (!should_close) {
        GLFW::PollEvents();
        Keyboard::next_frame();
        Time::next_frame();
        window->GetCursorPos(&posx, &posy);
        if (Keyboard::is_pressed(Key::W))
        {
            c.position = c.position - c.front * movespeed * Time::delta();
        }
        if (Keyboard::is_pressed(Key::S))
        {
            c.position = c.position + c.front * movespeed * Time::delta();
        }
        if (Keyboard::is_pressed(Key::A))
        {
            c.position = c.position - c.right * movespeed * Time::delta();
        }
        if (Keyboard::is_pressed(Key::D))
        {
            c.position = c.position + c.right * movespeed * Time::delta();
        }
        if (Keyboard::is_pressed(Key::LeftShift))
        {
            c.position = c.position - c.up * movespeed * Time::delta();
        }
        if (Keyboard::is_pressed(Key::Space))
        {
            c.position = c.position + c.up * movespeed * Time::delta();
        }
        if (Keyboard::is_releasing(Key::T))
        {
            if (mouseActive)
            {            
                mouseActive = false;
                glfwSetInputMode(glfw_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                window->SetCursorPos(width / 2, height / 2);
            }
            else {
                if (!mouseActive)
                {
                    mouseActive = true;
                    glfwSetInputMode(glfw_win, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                    window->SetCursorPos(width / 2, height / 2);
                }
            }
        }
        if (!mouseActive)
        {        
            float relX = posx - width / 2;
            float relY = posy - height / 2;
            if (abs(relX) > FLT_EPSILON)
            {
                c.front = glm::rotate(c.front, -relX * Time::delta() / glm::pi<float>(), c.up);
            }
            if (abs(relY) > FLT_EPSILON)
            {
                c.front = glm::rotate(c.front, -relY * Time::delta() / glm::pi<float>(), c.right);

            }
            window->SetCursorPos(width / 2, height / 2);
        }
        if (Keyboard::is_pressing(Key::Escape) || window->ShouldClose())
        {
            should_close = true;
            continue; // on revient au début de la boucle pour qu'elle ce quitte proprement.
        }

        View = glm::lookAt(
            c.position,
            c.position - c.front,
            glm::vec3(0, 1, 0)
        );

        glm::mat4 camTransform = glm::inverse(View);
        c.right = camTransform[0];
        c.up = camTransform[1];
        c.front = camTransform[2];

        glClearColor(0.0f, 0.0f, 0.4f, 0.0f); 
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,                  // attribute . No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
        );

        material->set_data("View", &View);
        material->set_data("LightWorld", &Light);
        material->set_data("LightColor", &LightColor);
        material->use();

        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < 10; j++)
            {
                glm::mat4 Model = glm::mat4(1.0f) * glm::translate(glm::vec3(i * 5, 0, j * 5));
                glm::mat4 mvp = Projection * View * Model;
                material->set_data("Model", &Model);
                material->set_data("MVP", &mvp);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
                glDrawElements(GL_TRIANGLES, indices.size(),GL_UNSIGNED_SHORT, (void*)0); // Starting from vertex 0; 3 vertices total -> 1 triangle
            }
        }
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("MyWindow");

        ImGui::Text("FPS: %f", 1.0f/Time::delta());
        ImGui::SliderFloat("lightX", &lightX, -50.0f, 50.0f);
        ImGui::SliderFloat("lightY", &lightY, -50.0f, 50.0f);
        ImGui::SliderFloat("lightZ", &lightZ, -50.0f, 50.0f);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        Light = glm::vec3{ lightX,lightY,lightZ };

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
