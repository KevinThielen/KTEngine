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
	    glm::vec3 worldPos = getWorldPosition();
	    
            if(xPos >= worldPos.x && xPos <= worldPos.x+width)
                if(yPos >= worldPos.y && yPos <= worldPos.y+ height)
                    return true;
            return false;
        }
        glm::vec3 getWorldPosition()
	{
	    TransformationComponent* parent = parentTransform;
	    glm::vec3 worldPos = glm::vec3(x,y,z);
	    
	    while(parent)
	    {
		worldPos += glm::vec3(parent->x, parent->y, parent->z);
		parent = parent->parentTransform;
	    };
	    return worldPos;
	}
        
        float x = 0, y = 0, z = 0;
        float width = 100.f, height = 100.f;
        float xRotation = 0, yRotation = 0, zRotation = 0;
        float xOffset = 0.0f, yOffset = 0.0f;
        TransformationComponent* parentTransform = nullptr;
    };
}
#endif