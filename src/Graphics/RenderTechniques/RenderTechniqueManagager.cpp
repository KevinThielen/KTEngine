#include <Graphics/RenderTechniques/BasicTechnique.h>
#include <Graphics/RenderTechniques/FontTechnique.h>
#include <Graphics/RenderTechniques/SpriteTechnique.h>

#include <Graphics/RenderTechniques/RederTechniqueManager.h>

namespace kte
{
    RenderTechniqueManager::~RenderTechniqueManager()
    {
        for(auto iterator = renderTechniques.begin(); iterator!=renderTechniques.end(); iterator++)
            delete iterator->second;
    }

    RenderTechniqueManager* RenderTechniqueManager::getInstance()
    {
        static RenderTechniqueManager renderTechniqueManager;
        return &renderTechniqueManager;
    }

    bool RenderTechniqueManager::initializeDefaultTechniques()
    {
        SpriteTechnique* spriteTech = new SpriteTechnique("default");
        renderTechniques[spriteTech->getName()] = spriteTech;

        BasicTechnique* basicTech = new BasicTechnique("basic");
        renderTechniques[basicTech->getName()] = basicTech;

        FontTechnique* tech = new FontTechnique("font");
        renderTechniques[tech->getName()] = tech;

        return true;
    }
    bool RenderTechniqueManager::addCustomTechnique(std::string name)
    {
        return false;
    }
}