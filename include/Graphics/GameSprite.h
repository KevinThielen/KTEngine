#ifndef KTE_GAME_SPRITE_H
#define KTE_GAME_SPRITE_H

#include <GameObject.h>
#include "GameObject.h"
#include "Components/SpriteComponent.h"
#include "Components/MouseInputComponent.h"
#include "Components/Animator.h"

namespace kte
{
    class GameSprite
    {
    public:
        GameSprite() {}
        GameSprite(GameObject *parent);

        GameSprite(GameObject *parent, glm::vec4 color);

        GameSprite(GameObject * parent, Texture *texture);

        void setColor(glm::vec4 color)
        {
            gameObject->getComponent<kte::SpriteComponent>()->color = color;
        }
        void setPosition(float x, float y)
        {
            TransformationComponent *trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->x = x;
            trans->y = y;
        }

        void setPosition(glm::vec2 position)
        {
            TransformationComponent *trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->x = position.x;
            trans->y = position.y;
        }


        void move(float dx, float dy)
        {
            TransformationComponent *trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->x += dx;
            trans->y += dy;
        }

        void setSize(float width, float height)
        {
            TransformationComponent *trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->width = width;
            trans->height = height;
        }

        void setSize(glm::vec2 size)
        {
            TransformationComponent *trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->width = size.x;
            trans->height = size.y;
        }

        void setRotationInDegrees(float rotation)
        {
            TransformationComponent* trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->zRotation = glm::radians(rotation);
        }

        void setLayer(unsigned int layer)
        {
            gameObject->getComponent<kte::SpriteComponent>()->layer = layer;
        }

        void setSpriteOffset(float xOffset, float yOffset)
        {
            SpriteComponent* sprite = gameObject->getComponent<SpriteComponent>();
            sprite->spriteOffsetX = xOffset;
            sprite->spriteOffsetY = yOffset;
        }

        glm::vec2 getPosition()
        {
            glm::vec2 position;
            TransformationComponent* trans = gameObject->getComponent<kte::TransformationComponent>();
            position.x = trans->x;
            position.y = trans->y;

            return position;
        }
        void setOnClickEvent(std::function<void(void)> function)
        {
            onClick = function;
            if(!gameObject->getComponent<MouseInputComponent>())
                gameObject->addComponent<MouseInputComponent>();

            gameObject->getComponent<MouseInputComponent>()->onClick = function;
        }

        void setTexture(Texture* texture)
        {
            SpriteComponent* sprite = gameObject->getComponent<SpriteComponent>();
            sprite->texture = texture;
        }

        void setParent(GameObject* parent)
        {
            gameObject->setParent(parent);
        }

        void setParent(GameSprite* parent)
        {
            gameObject->setParent(parent->getGameObject());
        }

        void mirror()
        {
            kte::SpriteComponent* spriteComponent = gameObject->getComponent<kte::SpriteComponent>();
            spriteComponent->mirrored = !spriteComponent->mirrored;
        }

        void setActive(bool isActive)
        {
            gameObject->setActive(isActive);
        }

        void moveUV(float x, float y)
        {
            kte::SpriteComponent* spriteComponent = gameObject->getComponent<kte::SpriteComponent>();
            glm::vec4 rect =  spriteComponent->textureRectangle;
            rect.x += x;
            if(rect.x > 1.0f)
                rect.x -= 1.0f;

            rect.y += y;
            if(rect.y > 1.0f)
                rect.y -= 1.0f;

            spriteComponent->textureRectangle = rect;
        }

        GameObject* getGameObject() { return gameObject; }
    private:
        GameObject* gameObject;
        std::function<void(void)> onClick;
    };
}
#endif