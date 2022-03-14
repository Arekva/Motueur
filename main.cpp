#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#ifdef _WIN32
#include <windows.h>
#endif
#include <SDL.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "glfw.hpp"
#include "keyboard.hpp"
#include "mesh.hpp"
#include "camera.hpp"


using namespace GLFW;
using namespace Motueur;

const int width = 800;
const int height = 600;
float movespeed = 0.1f;
float mousespeed = 0.1f;
const float ratio = width / height;

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path) {

    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if (VertexShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }
    else {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        //getchar();
        return 0;
    }

    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if (FragmentShaderStream.is_open()) {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;


    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const* VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
    glCompileShader(VertexShaderID);

    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }



    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const* FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
    glCompileShader(FragmentShaderID);

    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }



    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if (InfoLogLength > 0) {
        std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }


    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

void DrawCube(glm::vec3 corner1, glm::vec3 corner2)
{

    glBegin(GL_QUADS);
    glColor4f(0.0, 1.0, 1.0, 1.0);

    glVertex3f(corner1.x, corner1.y, corner1.z);
    glVertex3f(corner1.x, corner1.y, corner2.z);
    glVertex3f(corner1.x, corner2.y, corner2.z);
    glVertex3f(corner1.x, corner2.y, corner1.z);

    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3f(corner2.x, corner1.y, corner1.z);
    glVertex3f(corner2.x, corner1.y, corner2.z);
    glVertex3f(corner2.x, corner2.y, corner2.z);
    glVertex3f(corner2.x, corner2.y, corner1.z);

    glColor4f(1.0, 0.0, 0.0, 0.0);
    glVertex3f(corner1.x, corner1.y, corner1.z);
    glVertex3f(corner1.x, corner1.y, corner2.z);
    glVertex3f(corner2.x, corner1.y, corner2.z);
    glVertex3f(corner2.x, corner1.y, corner1.z);

    glColor4f(1.0, 0.0, 1.0, 1.0);
    glVertex3f(corner1.x, corner2.y, corner1.z);
    glVertex3f(corner1.x, corner2.y, corner2.z);
    glVertex3f(corner2.x, corner2.y, corner2.z);
    glVertex3f(corner2.x, corner2.y, corner1.z);

    glColor4f(1.0, 1.0, 0.0, 1.0);
    glVertex3f(corner1.x, corner1.y, corner1.z);
    glVertex3f(corner1.x, corner2.y, corner1.z);
    glVertex3f(corner2.x, corner2.y, corner1.z);
    glVertex3f(corner2.x, corner1.y, corner1.z);

    glColor4f(0.0, 1.0, 0.0, 1.0);
    glVertex3f(corner1.x, corner1.y, corner2.z);
    glVertex3f(corner1.x, corner2.y, corner2.z);
    glVertex3f(corner2.x, corner2.y, corner2.z);
    glVertex3f(corner2.x, corner1.y, corner2.z);

    glEnd();
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
        height,
        "Atom"
    );

    camera c;

    c.position = glm::vec3(1, 1, 1);
    c.horizontalRot = 3.14f;
    c.verticalRot = 0.0; 
    glm::vec3 direction = glm::vec3(cos(c.verticalRot) * sin(c.horizontalRot), sin(c.verticalRot), cos(c.verticalRot) * cos(c.horizontalRot));
    glm::vec3 right = glm::vec3(sin(c.verticalRot - M_PI / 2.0f), 0.0f, cos(c.verticalRot - M_PI / 2.0f));
    c.up = glm::cross(right, direction);
    
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;

    Window* window = win_handle->GetAPI();

    window->MakeContextCurrent();
    // glew
    glewInit();


    GLuint idtest = LoadShaders("../Motueur/shaders/VertexShader.glsl", "../Motueur/shaders/FragmentShader.glsl");

    GLuint MatrixID = glGetUniformLocation(idtest, "MVP");

    static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
    };

    
    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    

    //glUseProgram(idtest);


    // engine
    Mesh::init();

    Keyboard::init(window);

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    bool should_close = false;
    while(!should_close) {
        GLFW::PollEvents();
        Keyboard::next_frame();

        glm::vec3 direction = glm::vec3(cos(c.verticalRot) * sin(c.horizontalRot), sin(c.verticalRot), cos(c.verticalRot) * cos(c.horizontalRot));
        glm::vec3 right = glm::vec3(sin(c.verticalRot - M_PI / 2.0f), 0.0f, cos(c.verticalRot - M_PI / 2.0f));

        if(Keyboard::is_pressing(Key::Z))
        {

        }
        if (Keyboard::is_pressing(Key::Escape) || window->ShouldClose())
        {
            should_close = true;
            continue; // on revient au début de la boucle pour qu'elle ce quitte proprement.
        }/*
        View = glm::lookAt(
            c.position,
            c.position + direction,
            c.up
        );*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glFrustum(-1, 1,            -1 / ratio, 1 / ratio,            0.1, 1000);

        View = glm::lookAt(c.position,
            c.position + direction,
            c.up);

       // glLoadMatrixf(glm::value_ptr(View));

        /*
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
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);*/
        
        glBegin(GL_TRIANGLES);
        glColor4f(1.0, 0.0, 1.0, 1.0);
        glVertex3f(-1.0, -1.0, 0.0);
        glVertex3f(-1.0, 1.0, 0.0);
        glVertex3f(1.0, 1.0, 0.0);
        glEnd();

//        DrawCube(glm::vec3(-0.5,-0.5,-0.5), glm::vec3(0.5, 0.5, 0.5));
        window->SwapBuffers();
    }
}

int runThomas()
{
    SDL_Init(SDL_INIT_VIDEO);
    uint32_t windowsFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        windowsFlags);


    camera c;
    c.position = glm::vec3(0, 0, 0);
    c.horizontalRot = 3.14f;
    c.verticalRot = 0.0;
    glm::vec3 direction = glm::vec3(cos(c.verticalRot) * sin(c.horizontalRot), sin(c.verticalRot), cos(c.verticalRot) * cos(c.horizontalRot));
    glm::vec3 right = glm::vec3(sin(c.verticalRot - M_PI / 2.0f), 0.0f, cos(c.verticalRot - M_PI / 2.0f));
    glm::vec3 up = glm::cross(right, direction);
    glm::vec3 c1 = glm::vec3(-0.5, -0.5, -0.5);
    glm::vec3 c2 = glm::vec3(0.5, 0.5, 0.5);

    SDL_GLContext ctx = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, ctx);
    glewInit();

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    GLuint idtest = LoadShaders("../Motueur/shaders/VertexShader.glsl", "../source/Motueur/FragmentShader.glsl");

    static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };

    static const GLfloat g_color_buffer_data[] = {
    0.583f,  0.771f,  0.014f,
    0.609f,  0.115f,  0.436f,
    0.327f,  0.483f,  0.844f,
    0.822f,  0.569f,  0.201f,
    0.435f,  0.602f,  0.223f,
    0.310f,  0.747f,  0.185f,
    0.597f,  0.770f,  0.761f,
    0.559f,  0.436f,  0.730f,
    0.359f,  0.583f,  0.152f,
    0.483f,  0.596f,  0.789f,
    0.559f,  0.861f,  0.639f,
    0.195f,  0.548f,  0.859f,
    0.014f,  0.184f,  0.576f,
    0.771f,  0.328f,  0.970f,
    0.406f,  0.615f,  0.116f,
    0.676f,  0.977f,  0.133f,
    0.971f,  0.572f,  0.833f,
    0.140f,  0.616f,  0.489f,
    0.997f,  0.513f,  0.064f,
    0.945f,  0.719f,  0.592f,
    0.543f,  0.021f,  0.978f,
    0.279f,  0.317f,  0.505f,
    0.167f,  0.620f,  0.077f,
    0.347f,  0.857f,  0.137f,
    0.055f,  0.953f,  0.042f,
    0.714f,  0.505f,  0.345f,
    0.783f,  0.290f,  0.734f,
    0.722f,  0.645f,  0.174f,
    0.302f,  0.455f,  0.848f,
    0.225f,  0.587f,  0.040f,
    0.517f,  0.713f,  0.338f,
    0.053f,  0.959f,  0.120f,
    0.393f,  0.621f,  0.362f,
    0.673f,  0.211f,  0.457f,
    0.820f,  0.883f,  0.371f,
    0.982f,  0.099f,  0.879f
    };

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

    glm::mat4 View = glm::lookAt(
        glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
        glm::vec3(0, 0, 0), // and looks at the origin
        glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    glm::mat4 Model = glm::mat4(1.0f);

    glm::mat4 mvp = Projection * View * Model;


    GLuint MatrixID = glGetUniformLocation(idtest, "MVP");


    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glUseProgram(idtest);

    /*auto previous_time = std::chrono::steady_clock::now();
    float deltaTime;
    auto currtime = std::chrono::steady_clock::now();*/

    glEnable(GL_CULL_FACE);
    bool apprunning = true;
    while (apprunning)
    {/*
        currtime = std::chrono::steady_clock::now();
        float deltaTime = (float)std::chrono::duration_cast<std::chrono::nanoseconds>(previous_time - currtime).count() / 1E+9F;
        auto previous_time = currtime;*/
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
            direction = glm::vec3(cos(c.verticalRot) * sin(c.horizontalRot), sin(c.verticalRot), cos(c.verticalRot) * cos(c.horizontalRot));
            right = glm::vec3(sin(c.verticalRot - M_PI / 2.0f), 0.0f, cos(c.verticalRot - M_PI / 2.0f));

            if (curEvent.type == SDL_KEYDOWN) {
                if (curEvent.key.keysym.sym == SDLK_z)
                {
                    c.position = c.position + direction * movespeed;
                }
                if (curEvent.key.keysym.sym == SDLK_s)
                {
                    c.position = c.position - direction * movespeed;
                }
                if (curEvent.key.keysym.sym == SDLK_d)
                {
                    c.position = c.position + right * movespeed;
                }
                if (curEvent.key.keysym.sym == SDLK_q)
                {
                    c.position = c.position - right * movespeed;
                }
                if (curEvent.key.keysym.sym == SDLK_SPACE)
                {
                    c.position = c.position + up * movespeed;
                }
                if (curEvent.key.keysym.sym == SDLK_LSHIFT)
                {
                    c.position = c.position - up * movespeed;
                }
                if (curEvent.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 0;
                }
            }
            if (curEvent.type == SDL_MOUSEMOTION)
            {
                /*
                c.horizontalRot -= (curEvent.motion.x - width / 2) * mousespeed * deltaTime;
                c.verticalRot -= (curEvent.motion.y - height / 2) * mousespeed * deltaTime;*/
                SDL_WarpMouseInWindow(win, width / 2, height / 2);
            }
            if (curEvent.type == SDL_QUIT) return 0;

        }

        View = glm::lookAt(
            c.position,
            c.position + direction,
            up
        );

        glm::mat4 Model = glm::mat4(1.0f);

        glm::mat4 mvp = Projection * View * Model;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
        glColor4f(1.0, 0.0, 1.0, 1.0);



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
        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
        );

        glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);

        SDL_GL_SwapWindow(win);
    }
    return 0;
}

int main() {
    if(!startup()) return -1;

    runThomas();

    shutdown();

    return 0;
}
