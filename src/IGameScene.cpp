#include "IGameScene.h"
#include "Components/Camera.h"
#include "GameObject.h"
#include "Systems/RenderSystem.h"
#include "Systems/InputSystem.h"
#include "Systems/AnimationSystem.h"
kte::IGameScene::IGameScene()
{
    scene.reset(new kte::GameObject(this));
    scene->addComponent<kte::Camera>();
}

kte::IGameScene::~IGameScene()
{
    scene = NULL;
}

void kte::IGameScene::addSystem(kte::ISystem* system)
{
    systems.emplace_back(system);
    if(!system->init())
        kte::GameEngine::instance()->exit();
}

kte::GameObject* kte::IGameScene::getGameObject(unsigned int gameObjectId) { return gameObjects[gameObjectId]; }
void kte::IGameScene::addGameObject(GameObject* gameObject) { gameObjects[gameObject->getId()] = gameObject; }
void kte::IGameScene::removeGameObject(unsigned int gameObjectid) { gameObjects.erase(gameObjectid); }

void kte::IGameScene::initDefaultSystem()

    {
        //standard systems

        renderer = nullptr;
       addSystem(new RenderSystem);

        addSystem(new kte::AnimationSystem(&resources));
        addSystem(new kte::InputSystem);
    }

void kte::IGameScene::displayText(kte::Text text)
{
    renderer->displayText(text);
}
namespace kte
{
    bool isKeyDown(unsigned int key)
    {
        return Input::isKeyDown(key);
    }


}