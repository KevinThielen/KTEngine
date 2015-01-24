#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include <glm/glm.hpp>
#include "IComponent.h"

namespace kte
{
    struct SpriteComponent : public IComponent
    {
        std::string sprite;
        unsigned int layer = 0;

        float spriteOffsetX = 0;
        float spriteOffsetY = 0;
        glm::vec4 color;

        void setSpriteOffset(float x, float y) { spriteOffsetX = x; spriteOffsetY = y; }

    };
}
#endif