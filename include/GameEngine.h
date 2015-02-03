#ifndef KTE_GAME_ENGINE_H
#define KTE_GAME_ENGINE_H


/*
    The Main Class for the client.
    It manages the game scenes.
    There can only be one GameEngine-Instance per game
 */


#include <string>
#include "Window.h"
#include "IGameScene.h"

namespace kte
{
    struct WindowDesc
    {
        std::string title;
        int width;
        int height;

        WindowDesc(std::string title, int width = 800, int height = 600) : title(title), height(height), width(width)
        {
        }
    };

    class IGameScene;

    class GameEngine
    {
    public:
        static GameEngine* instance()
        {
            static GameEngine *instance = new GameEngine();
            return instance;
        }

        //run the game. The parameter is the first gameScene that should run.
        void run(IGameScene* initialScene, WindowDesc windowDesc);

        //exit the whole game
        void exit();

    private:
        //only one instance
        GameEngine() {}
        Window window;
        bool isRunning;
        std::unique_ptr<IGameScene> currentScene;
    };
}
#endif