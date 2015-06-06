
#include "Window.h"
#include "GameEngine.h"
/********************
* Creates the window and binds the current context to it.
* Also inits GLFW.
* Params:
*   std::string title: title of the Window
*   int width: Window width
*   int height: Window height
********************/
bool kte::Window::create(kte::WindowDesc windowDesc)
{

    //Destroy old window
    if (window != nullptr)
        destroy();

    // Initialise GLFW
    if (!glfwInit())
    {
	        std::cout<<"INIT"<<std::endl;
        return false;
    }

    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
glfwSwapInterval(1);

    // glfwSwapInterval(0);
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(windowDesc.width, windowDesc.height, windowDesc.title.c_str(), NULL, NULL);

    //window creation failed
    if (window == NULL)
    {
        destroy();
	        std::cout<<"NULL"<<std::endl;
    }
    glfwMakeContextCurrent(window);

    //	inputManager = InputManager(this->window);

    //glew
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
        std::cout<<"GLEW_OK"<<std::endl;
    //if (!GLEW_VERSION_3_1)
   //     return false;

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

//     enable Transparency
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);


    glClearColor(0.6f, 0.6f, 1.0f, 1.0f);
  //    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
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