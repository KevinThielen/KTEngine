#include <Graphics/RenderTechniques/RederTechniqueManager.h>
#include <Components/RenderComponent.h>
#include <Graphics/RenderTechniques/FontTechnique.h>
#include <Graphics/RenderSystem.h>
#include <Graphics/ShaderManager.h>
#include <Graphics/FontManager.h>
#include <Graphics/Text.h>
#include <iostream>
#include <Components/Camera.h>

#include <Engine.h>

namespace kte
{
    bool RenderSystem::initialize(std::string title, int width, int height)
    {
        if(!window.create(title, width, height))
            return false;

        //Load Shaders
        ShaderManager* shaderManager = kte::ShaderManager::getInstance();
        if (!shaderManager->shaderProgramFromFile("BasicShader", "Shaders/vertexShader.vs", "Shaders/fragmentShader.fs"))
            return false;

        if (!shaderManager->shaderProgramFromFile("FontShader", "Shaders/fontShader.vs", "Shaders/fontShader.fs"))
            return false;

        if(!RenderTechniqueManager::getInstance()->initializeDefaultTechniques())
            return false;
        if(!TextureManager::getInstance()->initializeDefaultTextures())
        {
            std::cout<<"Couldnt load default textures."<<std::endl;
            return false;
        }
        if(!MeshManager::getInstance()->initializeDefaultMeshes())
            return false;
        if(!FontManager::getInstance()->initializeDefaultFonts())
            return false;

        //dummy cam
        Camera::setMainCamera(Engine::getInstance()->addGameObject()->addComponent<Camera>());

        return true;
    }

    void RenderSystem::render(std::vector<GameObject*> gameObjects)
    {
        std::map<RenderTechnique*, std::vector<GameObject*>> goUsingTechnique;
        std::map<RenderTechnique*, std::vector<GameObject*>> goUsingTechniqueAlpha;

        for(int i = 0; i<gameObjects.size(); i++)
        {
            RenderComponent* renderComp = gameObjects[i]->getComponent<RenderComponent>();
            if(renderComp != NULL)
            {
                if(renderComp->isAlpha())
                    goUsingTechniqueAlpha[renderComp->getMaterial()->getRenderTechnique()].push_back(gameObjects[i]);
                else
                    goUsingTechnique[renderComp->getMaterial()->getRenderTechnique()].push_back(gameObjects[i]);
            }
        }

        for(auto techniqueList = goUsingTechnique.begin(); techniqueList != goUsingTechnique.end(); techniqueList++)
        {
            RenderTechnique* technique = techniqueList->first;
            if(technique != NULL)
            {
                technique->use();

                std::vector<GameObject*> goList = techniqueList->second;

                std::vector<GameObject*> goListAlphas = goUsingTechniqueAlpha[technique];


                techniqueList->first->render(goList);
                techniqueList->first->render(goListAlphas);
            }
        }



    }

    void RenderSystem::render(std::vector<Text*> guiTexts)
    {
        FontTechnique* technique = (FontTechnique*)(RenderTechniqueManager::getInstance())->getTechnique("font");
        technique->use();
        technique->render(guiTexts);
    }
}