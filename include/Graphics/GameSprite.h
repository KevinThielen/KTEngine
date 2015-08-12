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
        
        glm::vec4 getColor()
	{
	    return  gameObject->getComponent<kte::SpriteComponent>()->color;
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

        glm::vec2 getSize()
	{
	    TransformationComponent *trans = gameObject->getComponent<kte::TransformationComponent>();
            
	    glm::vec2 size = glm::vec2(trans->width, trans->height);
	    
	    return size;
	}
	
        void setRotationInDegrees(float rotation)
        {
            TransformationComponent* trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->zRotation = glm::radians(rotation);
        }

         void rotateByDegrees(float rotation, glm::vec2 offset)
        {
            TransformationComponent* trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->zRotation += glm::radians(rotation);
	    trans->xOffset = offset.x;
	    trans->yOffset = offset.y;
        }
        
        void rotateByDegrees(float rotation)
        {
            TransformationComponent* trans = gameObject->getComponent<kte::TransformationComponent>();
            trans->zRotation += glm::radians(rotation);
	    trans->xOffset = 0;
	    trans->yOffset = 0;
        }
        
        void setLayer(unsigned int layer)
        {
            gameObject->getComponent<kte::SpriteComponent>()->layer = layer;
        }

        unsigned int getLayer()
	{
	    return gameObject->getComponent<kte::SpriteComponent>()->layer;
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

        void setOnMouseOverEvent(std::function<void(void)> function)
        {
            onMouseOver = function;
            if(!gameObject->getComponent<MouseInputComponent>())
                gameObject->addComponent<MouseInputComponent>();

            gameObject->getComponent<MouseInputComponent>()->onMouseOver = function;
        }
        
        void setOnMouseLeaveEvent(std::function<void(void)> function)
        {
            onMouseLeave = function;
            if(!gameObject->getComponent<MouseInputComponent>())
                gameObject->addComponent<MouseInputComponent>();

            gameObject->getComponent<MouseInputComponent>()->onMouseLeave = function;
        }
        
        void setOnReleaseEvent(std::function<void(void)> function)
        {
            onRelease = function;
            if(!gameObject->getComponent<MouseInputComponent>())
                gameObject->addComponent<MouseInputComponent>();

            gameObject->getComponent<MouseInputComponent>()->onRelease = function;
        }
        void setOnDragEvent(std::function<void(float x, float y)> function)
	{
	    onDrag = function;
            if(!gameObject->getComponent<MouseInputComponent>())
                gameObject->addComponent<MouseInputComponent>();

            gameObject->getComponent<MouseInputComponent>()->onDrag = function;
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

        bool isMirrored()
	{
	    return gameObject->getComponent<kte::SpriteComponent>()->mirrored;
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

        void pauseOnClickListener(bool pause)
	{
	    gameObject->getComponent<MouseInputComponent>()->isActive = !pause;
	    
	}
	
        bool contains(glm::vec2 point)
	{
	    //TODO: Rotations
	    glm::vec2 position = getPosition();
	    glm::vec2 size = getSize();
	    
	    bool leftRightBoundary = (point.x >= position.x + size.x);
	    bool leftLeftBoundary = (point.x <= position.x);
	    bool leftTopBoundary = (point.y <= position.y);
	    bool leftBottomBoundary = (point.y >= position.y + size.y);
	    
	    return !(leftRightBoundary || leftLeftBoundary || leftTopBoundary || leftBottomBoundary);
	}
        
        glm::vec3 getWorldPosition() 
	{
	    return gameObject->getComponent<kte::TransformationComponent>()->getWorldPosition();
	}
	
        GameObject* getGameObject() { return gameObject; }
        
    private:
        GameObject* gameObject;
        std::function<void(void)> onClick;
        std::function<void(void)> onRelease;
        std::function<void(void)> onMouseOver;
        std::function<void(void)> onMouseLeave;
        std::function<void(float x, float y)> onDrag;;
    };
}
#endif