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
#include "Audio/AudioManager.h"
#include "Resources/Resources.h"


namespace kte
{
    class IGameScene;
    class GameObject;
    
    class GameEngine
    {
    public:
	virtual ~GameEngine()
	{
	    audioManager.release();
	}
	
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

	void popScene();
	GameObject* getSceneNode();
	IGameScene* getCurrentScene();
	
	Window* getContext() { return &window; }
	AudioManager* getAudioManager() { return &audioManager; }
	Resources* getResources() { return &resources; }
	void sendMessage(kte::Message* message);
	
    private:

        //only one instance
        GameEngine() {}
        Window window;
        bool isRunning;
        std::vector<std::unique_ptr<IGameScene>> gameScenes;
	FPSCounter fpsCounter;
	AudioManager audioManager;
	Resources resources;
	bool pop;
    };
}
#endif