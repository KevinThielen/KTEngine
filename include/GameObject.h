#ifndef KTE_GAME_OBJECT_H
#define KTE_GAME_OBJECT_H

#include "IGameScene.h"
#include "Messages/ComponentAddedMessage.h"
#include "Messages/GameObjectRemovedMessage.h"
#include "Components/IComponent.h"
#include "Components/TransformationComponent.h"


namespace kte
{
    class GameObject
    {
    public:
        GameObject(IGameScene* scene) : id(++ID_COUNTER), scene(scene)
        {
            parent = nullptr;
            addComponent<kte::TransformationComponent>()->parentTransform = nullptr;
            scene->addGameObject(this);
        }

        ~GameObject()
        {
            GameObjectRemovedMessage message;
            message.gameObjectId = id;
            scene->notifySystems(&message);
            scene->removeGameObject(id);
        }
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
            go->newParentRef(this);
            children.emplace_back(go);



            return go;
        }

       void addChild(GameObject* go)
        {
            children.emplace_back(go);
            go->newParentRef(this);
        }


        void addChild(std::shared_ptr<GameObject> refChild)
        {
            children.emplace_back(refChild);
            refChild->newParentRef(this);
        }

        std::shared_ptr<GameObject> getChild(unsigned int childId)
        {
            for(auto child : children)
            {
                if(child->getId() == childId)
                    return child;
            }
            return nullptr;
        }

        void newParentRef(GameObject* parent)
        {
            this->parent = parent;


            getComponent<kte::TransformationComponent>()->parentTransform = parent->getComponent<kte::TransformationComponent>();
            setActive(isActive);
        }


        void setParent(GameObject* newParent)
        {
            if(parent != newParent)
            {

                if (parent)
                {
                    GameObject* oldParent = parent;
                    newParent->addChild(parent->getChild(id));
                    oldParent->removeChild(getId());
                }
                else
                    newParent->addChild(this);
            }
        }

        void removeChild(unsigned int gameObjectId)
        {
            for(unsigned int i = 0; i<children.size(); i++)
            {
                if(children[i]->getId() == gameObjectId)
                {
                    children[i].reset();
                    children.erase(children.begin()+i);

                    return;
                }
                children[i]->removeChild(gameObjectId);
            }
        }

        void removeChild(GameObject* go)
        {
            for(unsigned int i = 0; i<children.size(); i++)
            {
                if(children[i]->getId() == go->getId())
                {
              //      children[i].reset();
                    children.erase(children.begin()+i);
                    return;
                }
                children[i]->removeChild(go->getId());
            }
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
        GameObject* parent = nullptr;
        std::vector<std::shared_ptr<GameObject>> children;
        std::vector<std::shared_ptr<IComponent>> components;

        bool isActive = true;
    };
}
#endif