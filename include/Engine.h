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

        void setOptions(std::string title, int width, int height) { this->title = title; this->width = width; this->height = height; }
        /*bool isKeyDown(int key) { return renderSystem.getWindow()->isKeyDown(key); }
        bool isMouseDown(int button) { return renderSystem.getWindow()->isMouseDown(button); }
        void getMousePosition(double* x, double* y) { return renderSystem.getWindow()->getMousePosition(x, y); }
        float getDeltaTime() { return dt; }
*/
        void setClearColor(glm::vec4 color) { renderSystem.getWindow()->setClearcolor(color.r, color.g, color.b, color.a); }

        kte::GameObject* getGameObject(unsigned int id)
        {
            for(int i = 0; i<gameObjects.size(); i++ )
                if(gameObjects[i]->getId() == id)
                    return gameObjects[i];
            return NULL;
        }

    private:
        Engine();
        ~Engine();
        bool initialize();
        void calculateFPS();

        std::string title;
        int width;
        int height;
        std::vector<std::unique_ptr<IGameState>> gameStates;
        std::vector<GameObject*> gameObjects;
        std::vector<Text*> guiTexts;

        bool isRunning;
        RenderSystem renderSystem;



        float lastTime = glfwGetTime();

    };
}

#endif