#ifndef KTE_MOVEMENT_COMPONENT_H
#define KTE_MOVEMENT_COMPONENT_H

#include <glm/glm.hpp>
#include "IComponent.h"

namespace kte
{
    class Texture;
    struct MovementComponent : public IComponent
    {
        MovementComponent(unsigned int gameObjectId) : IComponent(gameObjectId)
        {

        }
        glm::vec3 facing = glm::vec3(1,0,0);
        glm::vec3 direction = glm::vec3(0,0,0);
        float speed = 1.0f;
    };
}
#endif

