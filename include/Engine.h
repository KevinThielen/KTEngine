#ifndef KTE_ENGINE_H
#define KTE_ENGINE_H

#include <vector>
#include "Graphics/RenderSystem.h"


namespace kte
{
    class IGameState;
    class ShaderManager;

    class Engine
    {
    public:
        static Engine* getInstance();
        bool pushGameState(IGameState* gs);
        void popGameState();
        void run();
        void exit();
        GameObject* addGameObject();
        GameObject* addGameObject(glm::vec3 position, glm::vec3 scale = glm::vec3(1,1,1), glm::vec3 rotation = glm::vec3(0,0,0));
        GameObject* getGameObjectAt2DPosition(float x, float y);

        Text* createGuiText(Font* font, glm::vec3 position, glm::vec3 scale);

        void setOptions(std::string title, int width, int height) { this->title = title; this->width = width; this->height = height; }
        bool isKeyDown(int key) { return renderSystem.getWindow()->isKeyDown(key); }
        bool isMouseDown(int button) { return renderSystem.getWindow()->isMouseDown(button); }
        void getMousePosition(double* x, double* y) { return renderSystem.getWindow()->getMousePosition(x, y); }
    private:
        Engine();
        ~Engine();
        bool initialize();

        std::string title;
        int width;
        int height;
        std::vector<IGameState*> gameStates;
        std::vector<GameObject*> gameObjects;
        std::vector<Text*> guiTexts;

        bool isRunning;
        RenderSystem renderSystem;

        int fpsCounter = 0;
        int lastFrames = 0;
        float dt = 0.0f;
        double accumulatedTime = 0.0f;
        float frameTime = 0.0f;

        float lastTime = glfwGetTime();
    };
}

#endif