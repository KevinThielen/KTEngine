#ifndef KTE_SPRITE_TECHNIQUE_H
#define KTE_SPRITE_TECHNIQUE_H

#include <vector>
#include <GLFW/glfw3.h>

#include "RenderTechnique.h"
#include "Graphics/Geometries.h"
#include "Resources.h"

namespace kte
{
    class SpriteComponent;
    class TransformationComponent;

    class SpriteTechnique : public RenderTechnique
    {
    public:
        SpriteTechnique();
	virtual ~SpriteTechnique(){}
        virtual bool init();
        virtual void use();
        virtual void render(std::map<SpriteComponent*, TransformationComponent*> spritesToRender);


    private:

        GLuint programId;
        Quad* quad;
        GLuint defaultTexture;
        Resources resources;

    };
}
#endif