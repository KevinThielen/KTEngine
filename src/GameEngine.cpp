#include "GameEngine.h"

#include <iostream>
//run the game. The parameter is the first gameScene that should run.
void kte::GameEngine::run(IGameScene* initialScene, WindowDesc windowDesc)
{
    if(!window.create(windowDesc))
        return;

    currentScene = std::unique_ptr<IGameScene>(initialScene);
    if(!initialScene->init())
        return;
    //gameLoop
    isRunning = true;

    while(isRunning && !glfwWindowShouldClose(glfwGetCurrentContext()))
    {
        window.clearScreen();


        window.swapBuffers();
    }
}

//exit the whole game
void kte::GameEngine::exit()
{

}