#ifndef KTE_RENDERSYSTEM_H
#define KTE_RENDERSYSTEM_H

#include <vector>
#include "Window/Window.h"
#include "GameObject.h"
#include "Text.h"

namespace kte
{
    class GameObject;

    class RenderSystem
    {
    public:
        bool initialize(std::string title, int width, int height);
        void render(std::vector<GameObject*> gameObjects);
        void render(std::vector<Text*> guiTexts);

        Window* getWindow() { return &window; }
    private:
        Window window;
    };
}

#endif