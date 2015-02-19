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
        renderTechnique->use();
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

    //draw debug colliders
    for(auto collider : boxColliders)
    {
        RenderTechnique* technique = renderTechniques[0].get();
        std::map<SpriteComponent*, TransformationComponent*> debugSprites;

        technique->use();
        if(collider->isActive && collider->draw)
        {
            glDisable( GL_DEPTH_TEST );
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );

            TransformationComponent trans(0);
            trans.x = collider->position.x;
            trans.y = collider->position.y;
            trans.z = 0;
            trans.width = collider->size.x;
            trans.height = collider->size.y;
            trans.parentTransform = nullptr;

            SpriteComponent spriteComp(0);
            spriteComp.color = glm::vec4(0,0,1,0.4f);
            spriteComp.layer = 0;
            debugSprites[&spriteComp] = &trans;


            technique->render(debugSprites);
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL);
            glEnable( GL_DEPTH_TEST );

        }

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
        else if(dynamic_cast<kte::BoxCollider*>(componentAddedMessage->addedComponent))
        {
            boxColliders.push_back(dynamic_cast<kte::BoxCollider*>(componentAddedMessage->addedComponent));
        }
    }
}