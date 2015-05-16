#ifndef TRANSFORMATION_COMPONENT_H
#define TRANSFORMATION_COMPONENT_H

#include <glm/glm.hpp>
#include "IComponent.h"

namespace kte
{
    struct TransformationComponent : public IComponent
    {
        TransformationComponent(unsigned int gameObjectId) : IComponent(gameObjectId)
        {

        }

        bool contains(float xPos, float yPos)
        {
            if(xPos >= x && xPos <= x+width)
                if(yPos >= y && yPos <= y+ height)
                    return true;
            return false;
        }
        float x = 0, y = 0, z = 0;
        float width = 100.f, height = 100.f;
        float xRotation = 0, yRotation = 0, zRotation = 0;
        float xOffset = 0.0f, yOffset = 0.0f;
        TransformationComponent* parentTransform = nullptr;
    };
}
#endif