#include <iostream>

#include "Systems/AnimationSystem.h"


bool kte::AnimationSystem::init()
{
    return true;
}

void kte::AnimationSystem::update(float dt)
{
    for(auto animator : animators)
    {
        if(animator->isActive )
        {
            //change animation
            Animation* currentAnimation = nullptr;
            if (animator->playAnimation != "")
            {
                currentAnimation = resources->getAnimation(animator->playAnimation);
                animator->currentAnimation = currentAnimation;
                animator->playAnimation = "";
                animator->currentFrame = 0;
                animator->currentTime = 0.0f;
            }
            if(animator->currentAnimation)
            {
                currentAnimation = animator->currentAnimation;
                animator->currentTime += dt;
                if(animator->currentTime >= animator->speed)
                {
                    animator->currentTime = 0.0f;

                    if( animator->currentFrame >= currentAnimation->frames.size())
                    {
                        if(currentAnimation->repeat)
                        {
                            animator->currentFrame = 0;
                            //update spritcomponent
                            for(auto& spriteComponent : spriteComponents)
                            {
                                if(spriteComponent->gameObjectId == animator->gameObjectId)
                                {
                                    spriteComponent->texture = resources->getTexture(currentAnimation->spriteSheet);
                                    spriteComponent->textureRectangle = currentAnimation->frames[animator->currentFrame];
                                }
                            }
                            animator->currentFrame++;
                        }
                    }
                    else
                    {
                        //update spritcomponent
                        for(auto& spriteComponent : spriteComponents)
                        {
                            if(spriteComponent->gameObjectId == animator->gameObjectId)
                            {
                                spriteComponent->texture = resources->getTexture(currentAnimation->spriteSheet);
                                spriteComponent->textureRectangle = currentAnimation->frames[animator->currentFrame];
                            }
                        }
                        animator->currentFrame++;
                    }
                }
            }
        }
    }
}

void kte::AnimationSystem::receiveMessage(kte::Message* message)
{
    if(dynamic_cast<kte::ComponentAddedMessage*>(message))
    {
        ComponentAddedMessage* componentAddedMessage = dynamic_cast<kte::ComponentAddedMessage*>(message);

        if(dynamic_cast<kte::SpriteComponent*>(componentAddedMessage->addedComponent))
        {
            spriteComponents.push_back(dynamic_cast<kte::SpriteComponent*>(componentAddedMessage->addedComponent));
        }
        else if(dynamic_cast<kte::Animator*>(componentAddedMessage->addedComponent))
        {
            animators.push_back(dynamic_cast<kte::Animator*>(componentAddedMessage->addedComponent));
        }

    }
}