#ifndef KTE_INPUT_H
#define KTE_INPUT_H

#include <Window.h>
#include <glm/glm.hpp>

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

            return glm::vec2(x,y);
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