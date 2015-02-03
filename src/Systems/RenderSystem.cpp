#include "Systems/RenderSystem.h"
#include <iostream>
#include <map>
#include <Graphics/SpriteTechnique.h>

bool kte::RenderSystem::init()
{
    renderTechniques.emplace_back(new SpriteTechnique);
    if(!renderTechniques.back()->init())
        return false;
    return true;
}

void kte::RenderSystem::update(float dt)
{
    //pass the spriteComponents with the transformcomponents to their according rendertechniques
    for(auto& renderTechnique : renderTechniques)
    {
        std::map<SpriteComponent*, TransformationComponent*> spritesToRender;
        for(auto& spriteComponent : spriteComponents)
        {
            if(spriteComponent->isActive && spriteComponent->renderTechnique == renderTechnique->getName())
            {
                for(auto& transformationComponent : transformationComponents)
                {
                    if(transformationComponent->gameObjectId == spriteComponent->gameObjectId)
                    {
                        spritesToRender[spriteComponent] = transformationComponent;
                    }
                }
            }
        }
        renderTechnique->render(spritesToRender);
    }
}

void kte::RenderSystem::receiveMessage(kte::Message* message)
{
    if(dynamic_cast<kte::ComponentAddedMessage*>(message))
    {
        ComponentAddedMessage* componentAddedMessage = dynamic_cast<kte::ComponentAddedMessage*>(message);

        if(dynamic_cast<kte::SpriteComponent*>(componentAddedMessage->addedComponent))
        {
            spriteComponents.push_back(dynamic_cast<kte::SpriteComponent*>(componentAddedMessage->addedComponent));
        }
        else if(dynamic_cast<kte::TransformationComponent*>(componentAddedMessage->addedComponent))
        {
            transformationComponents.push_back(dynamic_cast<kte::TransformationComponent*>(componentAddedMessage->addedComponent));
        }
    }
}