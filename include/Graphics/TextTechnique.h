#ifndef KTE_TEXT_TECHNIQUE_H
#define KTE_TEXT_TECHNIQUE_H

#include <vector>
#include <GLFW/glfw3.h>

#include "RenderTechnique.h"
#include "Text.h"
#include "Graphics/Geometries.h"
#include "Resources/Resources.h"

namespace kte
{

    class TextTechnique : public RenderTechnique
    {
    public:
        TextTechnique();
	~TextTechnique() {}
        virtual bool init();
        virtual void use();
        virtual void render(std::map<SpriteComponent*, TransformationComponent*> spritesToRender){}
        void render(std::vector<Text> text);
        void render(Text text);

    private:
        GLuint programId;
        Quad* quad;
	Resources* resources;
    };
}
#endif