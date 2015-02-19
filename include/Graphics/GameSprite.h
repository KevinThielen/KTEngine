#ifndef KTE_GAME_SPRITE_H
#define KTE_GAME_SPRITE_H

#include <GameObject.h>
#include "GameObject.h"
#include "Components/SpriteComponent.h"

namespace kte
{
    class GameSprite
    {
    public:
        GameSprite(GameObject* parent);
        GameSprite(GameObject* parent, glm::vec4 color);
        GameSprite(GameObject*, Texture* texture);

        void setPosition(float x, float y)
        {
            TransformationComponent* trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->x = x;
            trans->y = y;
        }

        void setSize(float width, float height)
        {
            TransformationComponent* trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->width = width;
            trans->height = height;
        }

        void setLayer(unsigned int layer)
        {
            gameObject->getComponent<kte::SpriteComponent>()->layer = layer;
        }

        GameObject* getGameObject() { return gameObject; }
    private:
		GameSprite() {}

        GameObject* gameObject;
    };
}
#endif