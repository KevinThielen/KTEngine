
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
bool kte::Window::create(kte::WindowDesc windowDesc, bool fullscreen ) 
{
    desc = windowDesc;
    
  

    // Initialise GLFW
    
    if(!initialized)
	if (!glfwInit())
	    return false;

    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(1);

    // glfwSwapInterval(0);
    // Open a window and create its OpenGL context
    GLFWwindow* newWindow = nullptr;
    
    if(!fullscreen)
	newWindow = glfwCreateWindow(windowDesc.width, windowDesc.height, windowDesc.title.c_str(),nullptr, nullptr);
    else
	newWindow = glfwCreateWindow(windowDesc.width, windowDesc.height, windowDesc.title.c_str(),nullptr, nullptr);
	
    //window creation failed
    if (newWindow == nullptr)
    {
        destroy();
    }
    
      //Destroy old window
    if (window != nullptr)
       glfwDestroyWindow(window);
    
    
    window = newWindow;
    
  //  if(!initialized)
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    //	inputManager = InputManager(this->window);

    //glew
    if(!initialized)
    {
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	
	if(err != GL_NO_ERROR)
	{
	    std::cout<<"ERROR: "<<std::to_string(err)<< glewGetErrorString(err)<<std::endl;
	    return false;
	}
	
    }
  
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
    
    GLenum error = glGetError();
    if(error != GL_NO_ERROR)
    {
	std::cout<<"ERROR: "<<std::to_string(error)<< glewGetErrorString(error)<<std::endl;
    }
    initialized = true;
    
    return true;
}

bool kte::Window::create(bool fullscreen)
{
   return false;//create(desc, fullscreen);
    
}

void kte::Window::setFullscreen(bool fullscreen)
{
    //TODO:
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
    glfwSwapBuffers(glfwGetCurrentContext());
    glfwPollEvents();
    
    GLenum error = glGetError();
    while(error != GL_NO_ERROR)
    {
	std::cout<<"ERROR: "<<std::to_string(error)<< glewGetErrorString(error)<<std::endl;
	error = glGetError();
    }
    

}

void kte::Window::destroy()
{
    glfwTerminate();
    window = nullptr;
}