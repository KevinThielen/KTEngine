#include <iostream>
#include "Window/InputManager.h"

namespace kte
{

    InputManager::InputManager(GLFWwindow* window) : window(window)
    {
        mouseSpeed = 10;
    }


    bool InputManager::isKeyDown(unsigned int key)
    {
        return (glfwGetKey(window, key) == GLFW_PRESS);
    }

    bool InputManager::isMouseDown(unsigned int button)
    {
        return (glfwGetMouseButton(window, button) == GLFW_PRESS);
    }



    void InputManager::getMousePosition(double* x, double* y)
    {
        glfwGetCursorPos(window, x, y);
    }

    void InputManager::setMousePosition(double x, double y)
    {
        glfwSetCursorPos(window, x, y);
    }

    void InputManager::setMousePositionRelativ(float x, float y)
    {
        int width, height;
        glfwGetWindowSize(window, &width, &height);

        glfwSetCursorPos(window, width / (100 / x), height / (100 / y));
    }
}