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
        virtual bool init();
        virtual void use();
        virtual void render(std::map<SpriteComponent*, TransformationComponent*> spritesToRender);
        virtual void renderCached();

    private:

        struct VectorPointer
        {
        float *x,*y,*z;
        };
        struct RenderData
        {
            Texture* texture;
            std::vector<glm::mat4> mvps;
            std::vector<glm::vec4> colors;
            std::vector<glm::vec4> uvs;
        };


        GLuint programId;
        Quad* quad;
        GLuint defaultTexture;
        Resources resources;

        std::vector<RenderData> cachedSprites;
    };
}
#endif