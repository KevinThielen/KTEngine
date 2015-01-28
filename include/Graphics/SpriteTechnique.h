#ifndef KTE_SPRITE_TECHNIQUE_H
#define KTE_SPRITE_TECHNIQUE_H

#include <vector>
#include <GLFW/glfw3.h>

#include "RenderTechnique.h"
#include "Quad.h"


namespace kte
{
    class SpriteComponent;
    class TransformationComponent;

    class SpriteTechnique : public RenderTechnique
    {
    public:
        SpriteTechnique();
        virtual bool init();
        virtual void use();
        virtual void render(std::map<SpriteComponent*, TransformationComponent*> spritesToRender);
    private:
        GLuint programId;
        Quad quad;
    };
}
#endif