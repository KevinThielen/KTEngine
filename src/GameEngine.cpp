#include "GameEngine.h"

#include <iostream>
//run the game. The parameter is the first gameScene that should run.
void kte::GameEngine::run(IGameScene* initialScene, WindowDesc windowDesc, bool isMainLoop)
{
        kte::Profiler::track("StartUp");
    //gameLoop
    isRunning = true;
    pop = false;
    if(!window.create(windowDesc))
        return;

    

    if(!audioManager.initializeAudioDevice())
    {
	std::cout<<"Failed to initialize the AudioManager"<<std::endl;
	return;
    }
    
    kte::Input::setContext(&window);
    
    //default resources
    resources.loadPackage("KTEData");
    
    
    gameScenes.emplace_back(initialScene);
    initialScene->initDefaultSystem();

    if(!initialScene->init())
    {
	std::cout<<"Failed to initialize the scene."<<std::endl;
        return;
    }
    

    fpsCounter.update();
    kte::Profiler::stop("StartUp");
    
    if(isMainLoop)
    {
	while(isRunning && !glfwWindowShouldClose(window.getContext()))
	{
	    update();
	}
    }
}


void kte::GameEngine::update()
{
        kte::Profiler::track("GameLoop");
    	fpsCounter.update();

        window.clearScreen();

	if(!gameScenes.size())
	    return;

	float dt = fpsCounter.getDeltaTime();
	
	gameScenes.back()->IGameScene::update(dt);
        gameScenes.back()->update(dt);
	
        window.swapBuffers();
	
	if(pop)
	{
	    if(gameScenes.size())
	    {
		gameScenes.pop_back();
		
		if(gameScenes.size())
		    gameScenes.back()->refresh();
		
		pop = false;
	    }
	}
	
	    kte::Profiler::stop("GameLoop");
}

//exit the whole game
void kte::GameEngine::exit()
{
    isRunning = false;
}


void kte::GameEngine::pushScene(kte::IGameScene* scene)
{
    gameScenes.emplace_back(scene);
    scene->initDefaultSystem();
    if(!scene->init())
	gameScenes.pop_back();

}


void kte::GameEngine::popScene()
{
    pop = true;
}

kte::GameObject* kte::GameEngine::getSceneNode()
{
    return gameScenes.back()->getSceneNode();

    
}
kte::IGameScene* kte::GameEngine::getCurrentScene()
{	
    return gameScenes.back().get();
}


void kte::GameEngine::sendMessage(kte::Message* message)
{
    gameScenes.back()->notifySystems(message);	
}


