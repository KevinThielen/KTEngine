#include "IGameScene.h"
#include "Systems/RenderSystem.h"

kte::IGameScene::IGameScene()
{
    scene = std::unique_ptr<kte::GameObject>(new kte::GameObject(this));

    //stadard systems
    addSystem(new kte::RenderSystem);
}