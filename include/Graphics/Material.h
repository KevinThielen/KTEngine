#ifndef KTE_MATERIAL_H
#define KTE_MATERIAL_H

#include <glm/glm.hpp>
#include <Graphics/RenderTechniques/RederTechniqueManager.h>
#include <Graphics/RenderTechniques/Rendertechnique.h>
#include <Graphics/TextureManager.h>
namespace kte
{
    class Texture;

    class Material
    {
    public:
        Material()
        {
            renderTechnique = RenderTechniqueManager::getInstance()->getTechnique("default");
            color = glm::vec4(0,0,0,1);
            texture = TextureManager::getInstance()->getTexture("default.png");
        }
        RenderTechnique* getRenderTechnique() { return renderTechnique; }
        void setRenderTechnique(RenderTechnique* technique) { renderTechnique = technique; }

        glm::vec4 getColor() { return color; }
        void setColor(glm::vec4 color) { this->color = color; }

        Texture* getTexture() { return texture; }
        void setTexture(Texture* texture) { this->texture = texture; }
    private:
        RenderTechnique* renderTechnique;
        glm::vec4 color;
        Texture* texture;
    };
}

#endif