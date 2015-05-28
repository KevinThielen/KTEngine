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
#include <Messages/GameObjectRemovedMessage.h>

#include "GameEngine.h"
#include "Messages/Message.h"
#include "Systems/ISystem.h"
#include "Graphics/Text.h"
//#include "Systems/RenderSystem.h"
//#include "Systems/AnimationSystem.h"
//#include "Systems/InputSystem.h"
#include "Resources.h"
#include "Input.h"


namespace kte
{
    class GameObject;
    class RenderSystem;

    class IGameScene
    {
    public:
        IGameScene();

        virtual ~IGameScene();

        virtual bool init() = 0;
        virtual void update(float dt) { for (auto& system : systems) system->update(dt); }
        virtual void addSystem(ISystem* system);
        virtual void notifySystems(Message* message) { for(auto& system : systems) system->receiveMessage(message); }

        GameObject* getGameObject(unsigned int gameObjectId);
        void removeGameObject(unsigned int gameObjectid);
        void addGameObject(GameObject* gameObject);

        void displayText(Text text);

    protected:
        void initDefaultSystem();

        RenderSystem* renderer;
        std::shared_ptr<GameObject> scene;
        std::map<unsigned int, GameObject*> gameObjects;

        std::vector<std::unique_ptr<ISystem>> systems;
        kte::Resources resources;
    };

    bool isKeyDown(unsigned int key);
}


#include "GameObject.h"
#endif