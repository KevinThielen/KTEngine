/***********************
* Creates a simple Window with GLFW
* and serves as render context.
* Provides methods to clear and update the screen.
************************/

#ifndef KTE_WINDOW_H
#define KTE_WINDOW_H

#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Window/InputManager.h>


namespace kte
{
    class Window
    {
    public:

        /*********************
        * Constructor

        *********************/
        /********************
        * Creates the window and binds the current context to it.
        * Also inits GLFW.
        *
        * Params:
        *   std::string title: title of the Window
        *   int width: Window width
        *   int height: Window height
        ********************/
        bool create(std::string title, int width, int height);

        /*******************
        * Overrides the screen with the color set in glClearColor
        ********************/
        void clearScreen();

        /*******************
        * Swap the active buffer with the backbuffer.
        * Required to "Update" the screen.
        ********************/
        void swapBuffers();

        /*******************
        * Destroy the current window.
        ********************/
        void destroy();

        /***********************
        * SETTERS
        ***********************/
        void setClearcolor(float r, float g, float b, float a) { glClearColor(r, g, b, a); }

        bool isKeyDown(int key) { return inputManager.isKeyDown(key); }
        bool isMouseDown(int button) { return inputManager.isMouseDown(button); }
        void getMousePosition(double* x, double* y) { return inputManager.getMousePosition(x, y); }
    private:
        GLFWwindow* window;//contains the widnow context.
        int width; //window width
        int height; //window height
        InputManager inputManager;

    };
}


#endif
