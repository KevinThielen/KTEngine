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

#include "Resources/Resources.h"
#include "Input.h"
#include "Audio/AudioManager.h"

namespace kte
{
    class GameObject;
    class RenderSystem;

    class IGameScene
    {
    public:
        IGameScene();

        virtual ~IGameScene();

        virtual bool init() {}
        virtual void update(float dt) { for (auto& system : systems) system->update(dt); }
        virtual void addSystem(ISystem* system);
        virtual void notifySystems(Message* message) { for(auto& system : systems) system->receiveMessage(message); }
	virtual void refresh() { }
	
        GameObject* getGameObject(unsigned int gameObjectId);
        void removeGameObject(unsigned int gameObjectid);
        void addGameObject(GameObject* gameObject);


        void displayText(Text text);
        void displayText(std::vector<Text> texts);

        void initDefaultSystem();
    protected:

        RenderSystem* renderer;
        std::shared_ptr<GameObject> scene;
        std::map<unsigned int, GameObject*> gameObjects;

        std::vector<std::unique_ptr<ISystem>> systems;
        kte::Resources* resources;
	AudioManager* audioManager;
    };

    bool isKeyDown(unsigned int key);
}


#include "GameObject.h"
#endif