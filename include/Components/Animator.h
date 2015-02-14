#ifndef KTE_ANIMATOR_H
#define KTE_ANIMATOR_H

#include <glm/glm.hpp>
#include "IComponent.h"
#include "Graphics/Animation.h"
namespace kte
{
    struct Animator : public IComponent
    {
        Animator(unsigned int gameObjectId) : IComponent(gameObjectId)
        {

        }

        std::string playAnimation = "";
        float currentTime = 0.0f;
        unsigned int currentFrame = 0;
        float speed = 1.0f;
        Animation* currentAnimation = nullptr;
    };
}
#endif
