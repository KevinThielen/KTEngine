#ifndef KTE_INPUT_H
#define KTE_INPUT_H

#include <Window.h>
namespace kte
{
    class Input
    {
    public:
        static void setContext(kte::Window* window) {Input::window = window;}
        static bool isKeyDown(unsigned int key) { return window->isKeyDown(key); }

        
    private:
        Input(){}

        static Window* window;
    };
}

#endif