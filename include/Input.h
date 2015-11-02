#ifndef KTE_INPUT_H
#define KTE_INPUT_H

#include <Window.h>
#include "Components/Camera.h"
#include <glm/glm.hpp>
#include <iostream>
namespace kte
{
    class Input
    {
    public:
        static void setContext(kte::Window* window) {Input::window = window;}
        static bool isKeyDown(unsigned int key) { return window->isKeyDown(key); }
        static bool isMouseDown(unsigned int button = 0)
        {
            return glfwGetMouseButton(window->getContext(), button) == GLFW_PRESS;
        }
        static glm::vec2 getMousePosition()
        {
            double x,y;
            glfwGetCursorPos(window->getContext(), &x, &y);
	    kte::Camera* cam = kte::Camera::getMainCamera();
	    glm::vec2 screenResolution = window->getScreenResolution();
	    glm::vec2 virtualResolution = cam->getResolution();
	    
	    glm::vec2 scale;
	    scale.x = virtualResolution.x / screenResolution.x ;
	    scale.y =  virtualResolution.y / screenResolution.y;

	    glm::vec2 position = cam->getPosition();
            return glm::vec2(x * scale.x + position.x, y * scale.y + position.y);
        }
	
	static void enableCursor(bool enabled)
	{
	    if(!enabled)
		glfwSetInputMode(window->getContext(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	    else 
		glfwSetInputMode(window->getContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
        
        /*  void InputManager::setMousePosition(double x, double y)
    {
        glfwSetCursorPos(window, x, y);
    }

    void InputManager::setMousePositionRelativ(float x, float y)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        glfwSetCursorPos(window, width / (100 / x), height / (100 / y));
    }*/
    private:
        Input(){}

        static Window* window;
    };
}

#endif