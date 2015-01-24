#ifndef KTE_WINDOW_H
#define KTE_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace kte
{
    struct WindowDesc;

    class Window
    {
    public:
        bool create(kte::WindowDesc windowDesc);
        void clearScreen();
        void swapBuffers();
        void destroy();
    private:
        GLFWwindow* window;
    };
}

#endif