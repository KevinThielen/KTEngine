
#include "Window.h"
#include "GameEngine.h"
#include "Messages/ContextChange.h"
#include <Systems/RenderSystem.h>
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
    
    if(!initialized && !glfwInit())
	    return false;

    glfwWindowHint(GLFW_SAMPLES, 8);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwSwapInterval(0);

  //Destroy old window
    if (window != nullptr)
       glfwDestroyWindow(window);
    
    // Open a window and create its OpenGL context
    GLFWwindow* newWindow = nullptr;
    
    this->fullscreen = fullscreen;
    if(!fullscreen)
	newWindow = glfwCreateWindow(windowDesc.width, windowDesc.height, windowDesc.title.c_str(),nullptr, nullptr);
    else
    {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	desc.width = mode->width;
	desc.height = mode->height;
	newWindow = glfwCreateWindow(mode->width, mode->height, windowDesc.title.c_str(), glfwGetPrimaryMonitor(), nullptr);
    }
    //window creation failed
    if (newWindow == nullptr)
    {
        destroy();
    }
    
    window = newWindow;
    

    glfwMakeContextCurrent(window);

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


    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    RenderSystem::checkGLError("WindowCreation");
    initialized = true;
    
    return true;
}


void kte::Window::setFullscreen(bool fullscreen)
{
    if(this->fullscreen == fullscreen)
	return; 
    else 
    {
	this->fullscreen = fullscreen;
	reCreate = true;
    }
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
    
    RenderSystem::checkGLError("Swap Buffers");
   
    if(reCreate)
    {
    create(desc, fullscreen);  

    //release textures from old context
    GameEngine::instance()->getResources()->unload();
    RenderSystem::checkGLError("Ressources Unload");
    kte::Message* contextChange = new ContextChange();
    kte::GameEngine::instance()->sendMessage(contextChange);
    delete contextChange;
    RenderSystem::checkGLError("Window Recreation");
    
    //reallocate resources for new context
    GameEngine::instance()->getResources()->reload();
    RenderSystem::checkGLError("Ressources Reload");
    reCreate = false;
    }
}

void kte::Window::destroy()
{
    glfwTerminate();
    window = nullptr;
}