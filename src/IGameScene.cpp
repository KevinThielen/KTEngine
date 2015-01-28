#include "IGameScene.h"
#include "Systems/RenderSystem.h"

kte::IGameScene::IGameScene()
{
    scene = std::unique_ptr<kte::GameObject>(new kte::GameObject(this));

}

void kte::IGameScene::addSystem(kte::ISystem* system)
{
    systems.emplace_back(system);
    if(!system->init())
        kte::GameEngine::instance()->exit();
}