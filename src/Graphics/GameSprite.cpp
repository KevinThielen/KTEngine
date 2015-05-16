#include "Graphics/GameSprite.h"

kte::GameSprite::GameSprite(kte::GameObject* parent)
{
    gameObject = parent->addChild();
    gameObject->addComponent<kte::SpriteComponent>();

}


kte::GameSprite::GameSprite(kte::GameObject* parent, glm::vec4 color)
{
    gameObject = parent->addChild();
    gameObject->addComponent<kte::SpriteComponent>()->color = color;
}


kte::GameSprite::GameSprite(kte::GameObject* parent, kte::Texture* texture)
{
    gameObject = parent->addChild();
    gameObject->addComponent<kte::SpriteComponent>()->texture = texture;
}
