#ifndef IGameScene_h
#define IGameScene_h

/*
    Game Scene Interface
    The GameScene describes the current Scene.
    It contains the gameObjects with there positions, cameras, light sources, ect
    It's basicly a gameObject-Manager
 */

#include <memory>
#include <vector>

#include "GameEngine.h"
#include "Systems/ISystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/AnimationSystem.h"
#include "Resources.h"
#include "Input.h"


namespace kte
{
    class GameObject;
    class IGameScene
    {
    public:
        IGameScene();

        virtual ~IGameScene() {}

        virtual bool init() = 0;
        virtual void update(float dt) { for (auto& system : systems) system->update(dt); }
        virtual void addSystem(ISystem* system);
        virtual void notifySystems(Message* message)  { for(auto& system : systems) system->receiveMessage(message); }

        GameObject* getGameObject(unsigned int gameObjectId);
        void addGameObject(GameObject* gameObject);
    protected:
        void initDefaultSystem()
        {
            //stadard systems
            addSystem(new kte::MovementSystem);
            addSystem(new kte::RenderSystem);
            addSystem(new kte::AnimationSystem(&resources));

        }

        std::unique_ptr<GameObject> scene;
        std::map<unsigned int, GameObject*> gameObjects;

        std::vector<std::unique_ptr<ISystem>> systems;
        kte::Resources resources;
    };

    bool isKeyDown(unsigned int key);
}


#include "GameObject.h"
#endif