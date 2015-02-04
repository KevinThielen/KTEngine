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

        float x = 0, y = 0, z = 0;
        float width = 100.f, height = 100.f;
        float xRotation = 0, yRotation = 0, zRotation = 0;

        TransformationComponent* parentTransform = nullptr;
    };
}
#endif