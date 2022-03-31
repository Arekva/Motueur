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

extern "C" {
    _declspec(dllexport) uint32_t NvOptimusEnablement = 0x00000001;
}

void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id,
    GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    std::cout << "[OpenGL] " << message << std::endl;
}


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
float lightPow = 10000.0;
bool mouseActive;

glm::vec3 LightsWorld[32];
glm::vec4 LightsColor[32];
int LightNbr;

float lx = 0, ly = 0, lz = 0;

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

    GLFW::WindowHint::Generic(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);

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

void CreateLights(int LightsTobuild)
{
    if (LightsTobuild > 32) LightsTobuild = 32;
    for (int i = 0; i < LightsTobuild; i++)
    {
        LightsWorld[i] = glm::vec3{ 100.0 * (rand() / (float)RAND_MAX) ,100 * (rand() / (float)RAND_MAX) ,100.0 * (rand() / (float)RAND_MAX) };
        LightsColor[i] = glm::vec4{ rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,rand() / (float)RAND_MAX,lightPow };
    }
    LightNbr = LightsTobuild;
}

void run(GLFW::WindowInstance* win_handle) {
    LoadModel m;
    camera c;
    Window* window = win_handle->GetAPI();
    GLFWwindow* glfw_win = reinterpret_cast<GLFWwindow*>(window);

    window->MakeContextCurrent();

    glDebugMessageCallback(&glDebugOutput, nullptr);
    glDebugMessageControl(
        GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE);

    window->GetCursorPos(& posx, & posy);

    glfwSetInputMode(glfw_win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    mouseActive = false;

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // glew
    glewInit();

    CreateLights(32);

    //models 3D
    std:vector<unsigned short> indices;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normalsobj;
    std::vector<glm::vec3> tangent;
    std::vector<glm::vec3> bitangent;
    bool res = m.loadModel("assets\\models\\echelle.fbx", indices, vertices, uvs, normalsobj, tangent, bitangent);

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

    GLuint tangentbuffer;
    glGenBuffers(1, &tangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, tangent.size() * sizeof(glm::vec3), &tangent[0], GL_STATIC_DRAW);

    GLuint bitangentbuffer;
    glGenBuffers(1, &bitangentbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
    glBufferData(GL_ARRAY_BUFFER, bitangent.size() * sizeof(glm::vec3), &bitangent[0], GL_STATIC_DRAW);

    std::shared_ptr<Shader> shader = std::make_unique<Shader>("assets/shaders/thomas");

    glViewport(0, 0, width, height);

    c.position = glm::vec3(20, 20, 10);
    c.up = glm::vec3(0, 1, 0);

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 10000.0f);

    glm::mat4 View = glm::lookAt(
        c.position,
        glm::vec3(0, 0, 0), // and looks at the origin
        c.up
    );
    
    glm::mat4 camTransform = glm::inverse(View);
    c.right = camTransform[0];
    c.up = camTransform[1];
    c.front = camTransform[2];    

    Texture tex("assets/textures/cratediffuse.png");

    std::unique_ptr<Material> material = std::make_unique<Material>(shader);
    material->set_data("Texture", &tex);

    Texture nmap("assets/textures/cratenormal.png");
    material->set_data("NMap", &nmap);

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
            0,                  
            3,                  
            GL_FLOAT,           
            GL_FALSE,           
            0,                  
            (void*)0            
        );

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(
            1,                              
            2,                              
            GL_FLOAT,                       
            GL_FALSE,                       
            0,                              
            (void*)0                        
        );

        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
            2,                
            3,                
            GL_FLOAT,         
            GL_FALSE,         
            0,                
            (void*)0          
        );

        glEnableVertexAttribArray(3);
        glBindBuffer(GL_ARRAY_BUFFER, tangentbuffer);
        glVertexAttribPointer(
            3,                               
            3,                               
            GL_FLOAT,                        
            GL_FALSE,                        
            0,                               
            (void*)0                         
        );

        glEnableVertexAttribArray(4);
        glBindBuffer(GL_ARRAY_BUFFER, bitangentbuffer);
        glVertexAttribPointer(
            4,                               
            3,                               
            GL_FLOAT,                        
            GL_FALSE,                        
            0,                               
            (void*)0                         
        );

        material->set_data("View", &View);
        material->set_data("LightsWorld[0]", LightsWorld, LightNbr);
        material->set_data("LightsColor[0]", LightsColor, LightNbr);
        material->set_data("LightNbr", &LightNbr);
        material->use();

        for (size_t i = 0; i < 10; i++)
        {
            for (size_t j = 0; j < 20; j++)
            {
               // for (size_t k = 0; k < 10; k++)
                {
                    glm::mat4 Model = glm::mat4(1.0f) * glm::translate(glm::vec3(i * 6,0, j * 6));
                    glm::mat4 mvp = Projection * View * Model;
                    material->set_data("Model", &Model);
                    material->set_data("MVP", &mvp);
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesbuffer);
                    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, (void*)0);
                }
            }
        }
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        glDisableVertexAttribArray(4);

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        ImGui::Begin("MyWindow");
        
        ImGui::Text("FPS: %f", 1.0f/Time::delta());
        if (ImGui::Button("Re Gen Lights")) CreateLights(32);
        if (ImGui::SliderFloat("light pow", &lightPow, 0.0, 111000.0f))
        {
            for(int i = 0;i< LightNbr ;i++)
            {
                LightsColor[i][3] = lightPow;
            }
        }
        ImGui::SliderFloat("lx", &lx, 0.0, 100.0f);
        ImGui::SliderFloat("ly", &ly, 0.0, 100.0f);
        ImGui::SliderFloat("lz", &lz, 0.0, 100.0f);

        ImGui::End();
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        LightsWorld[0] = glm::vec3(lx, ly, lz);

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
