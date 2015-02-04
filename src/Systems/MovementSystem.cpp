#include <iostream>
#include "Systems/MovementSystem.h"


bool kte::MovementSystem::init()
{
    return true;
}

void kte::MovementSystem::update(__attribute__((unused)) float dt)
{
    for(auto movementComponent : movementComponents)
    {
        if(movementComponent->isActive)
        {
            for (auto &transformationComponent : transformationComponents)
            {
                if (movementComponent->gameObjectId == transformationComponent->gameObjectId)
                {
                    BoxCollider* boxCollider = nullptr;
                    bool intersects = false;

                    glm::vec3 deltaPos = movementComponent->direction;
                    if (glm::length(deltaPos) >= 1.0f)
                    {
                        deltaPos = glm::normalize(deltaPos);
                        deltaPos *= movementComponent->speed * dt;
                    }

                    for(auto& collider : boxColliders)
                    {
                        if(movementComponent->gameObjectId == collider->gameObjectId)
                        {
                            boxCollider = collider;
                        }
                    }

                    if(boxCollider && boxCollider->isActive)
                    {
                        BoxCollider checkbox(0);
                        checkbox.position = boxCollider->position + glm::vec2(deltaPos.x, deltaPos.y);
                        checkbox.size = boxCollider->size;

                        for (auto &collider : boxColliders)
                        {
                            if (movementComponent->gameObjectId != collider->gameObjectId)
                            {
                                if(checkbox.intersects(collider))
                                    intersects = true;
                            }
                        }
                    }

                    if(!intersects)
                    {
                        transformationComponent->x += deltaPos.x;
                        transformationComponent->y += deltaPos.y;
                        transformationComponent->z += deltaPos.z;

                        boxCollider->position.x += deltaPos.x;
                        boxCollider->position.y += deltaPos.y;
                    }
                    else
                        std::cout<<"COLLISION"<<std::endl;
                }
            }
        }
    }
}

void kte::MovementSystem::receiveMessage(kte::Message* message)
{
    if(dynamic_cast<kte::ComponentAddedMessage*>(message))
    {
        ComponentAddedMessage* componentAddedMessage = dynamic_cast<kte::ComponentAddedMessage*>(message);

        if(dynamic_cast<kte::MovementComponent*>(componentAddedMessage->addedComponent))
        {
            movementComponents.push_back(dynamic_cast<kte::MovementComponent*>(componentAddedMessage->addedComponent));
        }
        else if(dynamic_cast<kte::TransformationComponent*>(componentAddedMessage->addedComponent))
        {
            transformationComponents.push_back(dynamic_cast<kte::TransformationComponent*>(componentAddedMessage->addedComponent));
        }
        else if(dynamic_cast<kte::BoxCollider*>(componentAddedMessage->addedComponent))
        {
            boxColliders.push_back(dynamic_cast<kte::BoxCollider*>(componentAddedMessage->addedComponent));
        }
    }
}