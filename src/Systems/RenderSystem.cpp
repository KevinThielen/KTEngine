#include "Systems/RenderSystem.h"
#include <iostream>

bool kte::RenderSystem::init()
{
    return true;
}

void kte::RenderSystem::update(float dt)
{

}

void kte::RenderSystem::receiveMessage(std::string message)
{

    #if DEBUG
        std::cout<<message<<std::endl;
    #endif
}