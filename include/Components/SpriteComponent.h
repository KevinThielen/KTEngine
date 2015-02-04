#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <glm/glm.hpp>
#include "IComponent.h"

namespace kte
{
    class Texture;
    struct SpriteComponent : public IComponent
    {
        SpriteComponent(unsigned int gameObjectId) : IComponent(gameObjectId)
        {

        }

        std::string renderTechnique = "SpriteTechnique";
        Texture* texture = nullptr;
        int layer = 0;

        float spriteOffsetX = 0;
        float spriteOffsetY = 0;
        glm::vec4 color = glm::vec4(1,1,1,1);
        glm::vec4 textureRectangle = glm::vec4(0,0,1,1);
        void setSpriteOffset(float x, float y) { spriteOffsetX = x; spriteOffsetY = y; }
    };
}
#endif