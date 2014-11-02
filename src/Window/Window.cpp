
#include <iostream>
#include "Window/Window.h"



/********************
* Creates the window and binds the current context to it.
* Also inits GLFW.
* Params:
*   std::string title: title of the Window
*   int width: Window width
*   int height: Window height
********************/
bool kte::Window::create(std::string title, int width, int height)
{
    this->width = width;
    this->height = height;

    //Destroy old window
    if (window != NULL)
        destroy();

    // Initialise GLFW
    if (!glfwInit())
    {
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwSwapInterval(0);
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

    //window creation failed
    if (window == NULL)
    {
        destroy();
    }
    glfwMakeContextCurrent(window);

    //	inputManager = InputManager(this->window);

    //glew
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
        return false;
    if (!GLEW_VERSION_3_1)
        return false;

    std::cout<<"Init success"<<std::endl;
    // Enable depth test
    // glEnable(GL_DEPTH_TEST);

    //enable Transparency
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
    //  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    inputManager = InputManager(window);
    return true;
}

/*******************
* Overrides the screen with the color set in glClearColor
********************/
void kte::Window::clearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

/*******************
* Swap the active buffer with the backbuffer.
* Required to "Update" the screen.
********************/
void kte::Window::swapBuffers()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void kte::Window::destroy()
{
    glfwTerminate();
    window = NULL;
}
