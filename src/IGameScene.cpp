#include "IGameScene.h"
#include "Systems/RenderSystem.h"
#include "Components/Camera.h"
#include "GameObject.h"

kte::IGameScene::IGameScene()
{
	scene.reset(new kte::GameObject(this));
    scene->addComponent<kte::Camera>();
}

void kte::IGameScene::addSystem(kte::ISystem* system)
{
    systems.emplace_back(system);
    if(!system->init())
        kte::GameEngine::instance()->exit();
}

kte::GameObject* kte::IGameScene::getGameObject(unsigned int gameObjectId) { return gameObjects[gameObjectId]; }
void kte::IGameScene::addGameObject(GameObject* gameObject) { gameObjects[gameObject->getId()] = gameObject; }

namespace kte
{
    bool isKeyDown(unsigned int key)
    {
        return Input::isKeyDown(key);
    }
}