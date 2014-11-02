#ifndef FONT_TECHNIQUE_H
#define FONT_TECHNIQUE_H

#include <vector>
#include <Graphics/Text.h>
#include <Graphics/ShaderManager.h>
#include <Graphics/RenderTechniques/Rendertechnique.h>
#include <Graphics/Texture.h>
/*****************************
* A simple RenderTechnique for redering text.
******************************/

namespace kte
{
    class FontTechnique : public RenderTechnique
    {
    public:
        FontTechnique(std::string name);
        virtual void use();
        virtual void render(std::vector<GameObject*> gameObjects) { std::cout<<"No support for gameObjects!"; }
        void render(std::vector<Text*> texts);
    private:
        GLuint programId;
        GLuint currentTexture;
    };
}
#endif