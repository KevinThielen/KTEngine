#ifndef KTE_GAME_OBJECT_H
#define KTE_GAME_OBJECT_H

#include "IGameScene.h"

namespace kte
{
    class GameObject
    {
    public:
        GameObject(IGameScene* scene) : id(++ID_COUNTER), scene(scene)
        {
        }

        ~GameObject() {}
        template <typename T> T*  addComponent()
        {

            scene->notifySystems("new Component");
        }

        GameObject* addChild()
        {
            GameObject* go = new GameObject(scene);
            children.emplace_back(go);

            return go;
        }

    private:
        unsigned int id;
        static unsigned int ID_COUNTER;
        IGameScene* scene;

        std::vector<std::unique_ptr<GameObject>> children;
    };
}
#endif