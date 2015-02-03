#include "IGameScene.h"
#include "Systems/RenderSystem.h"
#include "Components/Camera.h"

kte::IGameScene::IGameScene()
{
    scene = std::unique_ptr<kte::GameObject>(new kte::GameObject(this));
    scene->addComponent<kte::Camera>();
}

void kte::IGameScene::addSystem(kte::ISystem* system)
{
    systems.emplace_back(system);
    if(!system->init())
        kte::GameEngine::instance()->exit();
}