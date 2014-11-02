#ifndef KTE_RENDERCOMPONENT_H
#define KTE_RENDERCOMPONENT_H

#include <Graphics/Material.h>
#include <Components/IComponent.h>
#include <Graphics/MeshManager.h>
#include <Graphics/RenderTechniques/RederTechniqueManager.h>

namespace kte
{
    class Mesh;
    class RenderTechnique;


    class RenderComponent : public IComponent
    {
    public:
        RenderComponent(unsigned int gameObjectId) : IComponent(gameObjectId)
        {
            material = Material();
            mesh = MeshManager::getInstance()->getMesh("Quad");
        }


        void setMesh(Mesh* mesh) { this->mesh = mesh; }
        void setMaterial(Material material) { this->material = material; }

        Mesh* getMesh() { return mesh; }
        Material* getMaterial() { return &material; }

        bool isAlpha() { return alpha; }
        void isAlpha(bool alpha) { this->alpha = alpha; }

    private:
        Mesh* mesh;
        Material material;
        bool alpha  =false;
    };
}
#endif