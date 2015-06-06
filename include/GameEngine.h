#ifndef KTE_GAME_ENGINE_H
#define KTE_GAME_ENGINE_H


/*
    The Main Class for the client.
    It manages the game scenes.
    There can only be one GameEngine-Instance per game
 */

#define GLM_FORCE_RADIANS
#include <string>
#include "Window.h"
#include "IGameScene.h"
#include "Input.h"
#include "Utility/FPSCounter.h"

namespace kte
{
    struct WindowDesc
    {
        std::string title;
        int height;
        int width;

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
            static std::unique_ptr<GameEngine> instance = std::unique_ptr<GameEngine>(new GameEngine);
            return instance.get();
        }

        //run the game. The parameter is the first gameScene that should run.
        void run(IGameScene* initialScene, WindowDesc windowDesc, bool isMainloop = true);

	
	void update();
        
	
	//exit the whole game
        void exit();
	
	void pushScene(IGameScene* scene);

	void popScene()
	{
	    if(gameScenes.size())
	    {
		gameScenes.pop_back();
		  
	    }
	}
    private:

        //only one instance
        GameEngine() {}
        Window window;
        bool isRunning;
        std::vector<std::unique_ptr<IGameScene>> gameScenes;
	FPSCounter fpsCounter;
    };
}
#endif