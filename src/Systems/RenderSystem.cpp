#include "Systems/RenderSystem.h"
#include <iostream>
#include <map>
#include <Graphics/SpriteTechnique.h>
#include <Graphics/TextTechnique.h>
#include <Graphics/ShaderManager.h>
#include <GameEngine.h>

bool kte::RenderSystem::init()
{  
    Geometries::initialze();

    renderTechniques.emplace_back(new SpriteTechnique);
    if(!renderTechniques.back()->init())
        return false;

    textTechnique.reset(new TextTechnique);
    if(!textTechnique->init())
      return false;

    resources = kte::GameEngine::instance()->getResources();
    
    if(!postProcessing.initialize())
      return false;
    
    postProcessing.setTechnique(renderTechniques.back().get());
    checkGLError("PostProcessing");
    
    return true;
}

void kte::RenderSystem::update(float dt)
{
//     postProcessing.bind();
    std::vector<GLuint> renderTextures;
    //pass the spriteComponents with the transformcomponents to their according rendertechniques
    for(auto& renderTechnique : renderTechniques)
    {
        renderTechnique->use();
        if(componentsChanged)
        {
            spritesToRender.clear();
            for (auto& spriteComponent : spriteComponents)
            {
                if (spriteComponent.second->isActive && spriteComponent.second->renderTechnique == renderTechnique->getName())
                {
                    if (transformationComponents[spriteComponent.second->gameObjectId])
                        spritesToRender[spriteComponent.second] = transformationComponents[spriteComponent.second->gameObjectId];
                }

            }
            componentsChanged = true;
//            componentsChanged = false;
	    
            renderTechnique->render(spritesToRender);
	    renderTextures.push_back(renderTechnique->getRenderTexture());
        }
   //     else
   //        renderTechnique->renderCached();


    }
    
    postProcessing.bind();

    checkGLError("POSTPROCESSING");
    for(auto& textToRender : textsToRender)
    {
	Text* text = &textToRender.second;
	TextComponent* textComp = textComponents[textToRender.first];
	text->isActive(textComp->isActive);
	
	if(textComp->isActive)
	{
	    TransformationComponent* trans = transformationComponents[textToRender.first];
	    
	    if(text->getFontName() != textComp->font)
		text->setFont(resources->getFont(textComp->font));
	    
	    if(text->getString() != textComp->text)
		text->setString(textComp->text);
	    
	    text->setPosition(trans->x + textComp->xOffset, trans->y + textComp->yOffset);
	    
	    if(textComp->colors.size() > 0)
		text->setColors(textComp->colors);
	    else text->setColor(textComp->color);
	}
    }
    
    for(auto texture : renderTextures)
	postProcessing.render(texture);
        
    textTechnique->render(textsToRender);
    //draw debug colliders
/*    for(auto collider : boxColliders)
    {
        RenderTechnique* technique = renderTechniques[0].get();
        std::map<SpriteComponent*, TransformationComponent*> debugSprites;

     
        if(collider->isActive && collider->draw)
        {   
			technique->use();
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

    }*/
}

void kte::RenderSystem::receiveMessage(kte::Message* message)
{
    if(dynamic_cast<kte::ComponentAddedMessage*>(message))
    {
        ComponentAddedMessage* componentAddedMessage = dynamic_cast<kte::ComponentAddedMessage*>(message);

        if(dynamic_cast<kte::SpriteComponent*>(componentAddedMessage->addedComponent))
        {
            componentsChanged = true;
            spriteComponents[componentAddedMessage->gameObjectId] = (dynamic_cast<kte::SpriteComponent*>(componentAddedMessage->addedComponent));
        }
        else if(dynamic_cast<kte::TransformationComponent*>(componentAddedMessage->addedComponent))
        {
            componentsChanged = true;
            transformationComponents[componentAddedMessage->gameObjectId]=dynamic_cast<kte::TransformationComponent*>(componentAddedMessage->addedComponent);
        }
        else if(dynamic_cast<kte::BoxCollider*>(componentAddedMessage->addedComponent))
        {
            boxColliders.push_back(dynamic_cast<kte::BoxCollider*>(componentAddedMessage->addedComponent));
        }
        else if(dynamic_cast<kte::TextComponent*>(componentAddedMessage->addedComponent))
        {
            componentsChanged = true;
            textComponents[componentAddedMessage->gameObjectId] = dynamic_cast<kte::TextComponent*>(componentAddedMessage->addedComponent);
	    
	    TextComponent* comp = textComponents[componentAddedMessage->gameObjectId];
	    textsToRender[componentAddedMessage->gameObjectId].setColor(comp->color);
	    textsToRender[componentAddedMessage->gameObjectId].setString("");
	    
	    
        }
    }
    if(dynamic_cast<kte::GameObjectRemovedMessage*>(message))
    {
        GameObjectRemovedMessage* gameObjectRemovedMessage = dynamic_cast<kte::GameObjectRemovedMessage*>(message);

        if(spriteComponents.count(gameObjectRemovedMessage->gameObjectId))
        {
            componentsChanged = true;
            spriteComponents.erase(gameObjectRemovedMessage->gameObjectId);
        }
        if(transformationComponents.count(gameObjectRemovedMessage->gameObjectId))
        {
            componentsChanged = true;
            transformationComponents.erase(gameObjectRemovedMessage->gameObjectId);
        }
        if(textComponents.count(gameObjectRemovedMessage->gameObjectId))
        {
            componentsChanged = true;
            textComponents.erase(gameObjectRemovedMessage->gameObjectId);
        }
    }
    if(dynamic_cast<kte::ContextChange*>(message))
    {
	    checkGLError("Context Change Entry");
	    ShaderManager::instance()->reset();
	    checkGLError("ShaderManager reset");
	    Geometries::reCreate();
	    checkGLError("Geometry Recreation");
    
	    
	    renderTechniques.clear();
	    
	    renderTechniques.emplace_back(new SpriteTechnique);
	    renderTechniques.back()->init();
	    checkGLError("SpriteTechnique init");

	    textTechnique.reset(new TextTechnique);
	    textTechnique->init();
	    checkGLError("TextTechnique init");
	    
	    postProcessing.reload();
    }

}