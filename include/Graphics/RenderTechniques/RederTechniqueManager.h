#ifndef KTE_RENDERTECHNIQUE_MANAGER_H
#define KTE_RENDERTECHNIQUE_MANAGER_H

#include <string>
#include <map>
#include <Graphics/RenderTechniques/Rendertechnique.h>

namespace kte
{
    //Singleton
    class RenderTechniqueManager
    {
    public:
        ~RenderTechniqueManager();
        static RenderTechniqueManager* getInstance();
        bool initializeDefaultTechniques();
        bool addCustomTechnique(std::string name);

        RenderTechnique* getTechnique(std::string name) { return renderTechniques[name]; }
    private:
        RenderTechniqueManager(){}

        std::map<std::string, RenderTechnique*> renderTechniques;
    };
}
#endif