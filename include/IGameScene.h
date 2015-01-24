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

#include "Systems/ISystem.h"


namespace kte
{
    class GameObject;
    class IGameScene
    {
    public:
        IGameScene();

        virtual ~IGameScene() {}

        virtual bool init() = 0;
        virtual void update(float dt) = 0;
        virtual void addSystem(ISystem* system) { systems.emplace_back(system); }
        virtual void notifySystems(std::string message)  { for(auto& system : systems) system->receiveMessage(message); }

    protected:
        std::unique_ptr<GameObject> scene;
        std::vector<std::unique_ptr<ISystem>> systems;
    };
}

#include "GameObject.h"
#endif