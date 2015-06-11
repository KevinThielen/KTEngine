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
	Window() { window = nullptr; }
        bool create(kte::WindowDesc windowDesc);
        void clearScreen();
        void swapBuffers();
        void destroy();
        GLFWwindow* getContext() { return window; }
        bool isKeyDown(unsigned int key) { return glfwGetKey(window, key); }
        void setWireframe() {  glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); }
    private:
        GLFWwindow* window;
    };
}

#endif