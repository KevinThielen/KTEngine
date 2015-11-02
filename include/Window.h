#ifndef KTE_WINDOW_H
#define KTE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>
#include <string>
#include <glm/glm.hpp>

namespace kte
{
    struct WindowDesc
    {
        std::string title;
        int height;
        int width;

        WindowDesc(std::string title = "empty", int width = 800, int height = 600) : title(title), height(height), width(width)
        {
        }
    };
    
    class Window
    {
    public:
	Window() { window = nullptr; initialized = false; reCreate = false;}
        bool create(kte::WindowDesc windowDesc, bool fullscreen = false );
        void clearScreen();
        void swapBuffers();
        void destroy();
        GLFWwindow* getContext() { return window; }
        bool isKeyDown(unsigned int key) { return glfwGetKey(window, key); }
        void setWireframe() {  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); }
        
        void setBackgroundColor(float r, float g, float b) { glClearColor(r, g, b, 1.0f); }
	void setFullscreen(bool fullscreen);
        
        
        //setting stuff
        std::vector<glm::vec2> getScreenResolutions()
	{
	    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	    
	    std::vector<glm::vec2> resolutions;
	    
	    if(monitor)
	    {
		int modeCount;
		const GLFWvidmode* modes = glfwGetVideoModes(monitor, &modeCount);
	    
	    
		for(int i = 0; i<modeCount; i++)
		    resolutions.push_back(glm::vec2(modes[i].width, modes[i].height));
	    }
	    return resolutions;
	}
    
	glm::vec2 getScreenResolution() { return glm::vec2(desc.width, desc.height); }
	
	void setScreenResolution(glm::vec2 resolution)
	{
	   desc.width = resolution.x;
	   desc.height = resolution.y;
	   
	   reCreate = true;
	}
	
    private:
        GLFWwindow* window;
	WindowDesc desc;
	
	bool initialized;
	bool reCreate;
	bool fullscreen;
    };
}

#endif