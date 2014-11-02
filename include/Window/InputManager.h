#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <GLFW/glfw3.h>

namespace kte
{
    class InputManager
    {
    public:
        InputManager(){}
        InputManager(GLFWwindow* window);

        bool isKeyDown(unsigned int key);
        bool isMouseDown(unsigned int key);

        void getMousePosition(double* x, double* y);

        void setMousePosition(double x, double y);
        void setMousePositionRelativ(float x, float y);

        float getMouseSpeed() { return mouseSpeed; }
        void getMouseSpeed(float s) { mouseSpeed = s; }

    private:
        GLFWwindow* window;
        float mouseSpeed;
    };
}
#endif