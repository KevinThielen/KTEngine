#ifndef KTE_GAME_OBJECT_H
#define KTE_GAME_OBJECT_H


#include "Messages/ComponentAddedMessage.h"
#include "Components/IComponent.h"
#include "Components/TransformationComponent.h"
#include "IGameScene.h"

namespace kte
{
    class GameObject
    {
    public:
        GameObject(IGameScene* scene) : id(++ID_COUNTER), scene(scene)
        {
            addComponent<kte::TransformationComponent>()->parentTransform = nullptr;
            scene->addGameObject(this);
        }

        virtual ~GameObject() {}
        template <typename T> T*  addComponent()
        {
            ComponentAddedMessage message;
            message.addedComponent = new T(id);
            message.gameObjectId = id;

            scene->notifySystems(&message);
            components.emplace_back(message.addedComponent);
            message.addedComponent->isActive = isActive;

            return dynamic_cast<T*>(message.addedComponent);
        }

        template <typename T> T* getComponent()
        {
            for(auto& comp : components)
            {
                IComponent* baseComp = comp.get();
                if(dynamic_cast<T*>(baseComp))
                    return dynamic_cast<T*>(baseComp);
            }

            return nullptr;
        }

        GameObject* addChild()
        {
            GameObject* go = new GameObject(scene);
            children.emplace_back(go);

            go->getComponent<kte::TransformationComponent>()->parentTransform = getComponent<kte::TransformationComponent>();
            go->setActive(isActive);

            return go;
        }

        void setActive(bool active)
        {
            isActive = active;
            for(auto& component : components)
                component->isActive = active;
            for(auto& child : children)
                child->setActive(active);
        }

        unsigned int getId() { return id; }
    private:
        unsigned int id;
        static unsigned int ID_COUNTER;
        IGameScene* scene;

        std::vector<std::unique_ptr<GameObject>> children;
        std::vector<std::unique_ptr<IComponent>> components;
        bool isActive = true;
    };
}
#endif