#include "GameEngine.h"

#include <iostream>
//run the game. The parameter is the first gameScene that should run.
void kte::GameEngine::run(IGameScene* initialScene, WindowDesc windowDesc, bool isMainLoop)
{
    //gameLoop
    isRunning = true;
    pop = true;
    if(!window.create(windowDesc))
        return;

    

    if(!audioManager.initializeAudioDevice())
    {
	std::cout<<"Failed to initialize the AudioManager"<<std::endl;
	return;
    }
    
    kte::Input::setContext(&window);
    
    gameScenes.emplace_back(initialScene);
    initialScene->initDefaultSystem();

    if(!initialScene->init())
    {
	std::cout<<"Failed to initialize the scene."<<std::endl;
        return;
    }
    

    fpsCounter.update();
    
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
    	fpsCounter.update();

        window.clearScreen();

	if(!gameScenes.size())
	    return;

	float dt = fpsCounter.getDeltaTime();
	
	gameScenes.back()->IGameScene::update(dt);
        gameScenes.back()->update(dt);
	
        window.swapBuffers();
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
    if(gameScenes.size())
    {
	gameScenes.pop_back();
	
	if(gameScenes.size())
	    gameScenes.back()->refresh();
    }
}


