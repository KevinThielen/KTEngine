#include "GameEngine.h"

#include <iostream>
//run the game. The parameter is the first gameScene that should run.
void kte::GameEngine::run(IGameScene* initialScene, WindowDesc windowDesc)
{
    //gameLoop
    isRunning = true;

    if(!window.create(windowDesc))
        return;

    kte::Input::setContext(&window);
    currentScene.reset(initialScene);

    if(!initialScene->init())
        return;

	fpsCounter.update();
    while(isRunning && !glfwWindowShouldClose(glfwGetCurrentContext()))
    {
		fpsCounter.update();

        window.clearScreen();

        currentScene->update(fpsCounter.getDeltaTime());
        window.swapBuffers();
    }
}

//exit the whole game
void kte::GameEngine::exit()
{
    isRunning = false;
}

