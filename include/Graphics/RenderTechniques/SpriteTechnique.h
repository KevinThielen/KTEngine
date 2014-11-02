#ifndef SPRITE_TECHNIQUE_H
#define SPRITE_TECHNIQUE_H

#include <vector>
#include <Graphics/ShaderManager.h>
#include <Graphics/RenderTechniques/Rendertechnique.h>
#include <Graphics/Texture.h>
/*****************************
* A simple RenderTechnique. It takes the gameObjects and displays them
* according to their meshs and their material color, without lighting or textures
******************************/

namespace kte
{
    class SpriteTechnique : public RenderTechnique
    {
    public:
        SpriteTechnique(std::string name);
        virtual void use();
        virtual void render(std::vector<GameObject*> gameObjects);
    private:
        GLuint programId;
        GLuint texture;
    };
}
#endif