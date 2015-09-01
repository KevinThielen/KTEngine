#ifndef KTE_BOX_COLLIDER_H
#define KTE_BOX_COLLIDER_H

#include <glm/glm.hpp>
#include <functional>
#include <algorithm> //std::function
#include "IComponent.h"

namespace kte
{
    struct BoxCollider : public IComponent
    {
        BoxCollider(unsigned int gameObjectId) : IComponent(gameObjectId)
        {
	    onCollision = [] () {};
        }

        bool intersects(BoxCollider* other)
        {
            if(other->position.x > position.x + size.x ||
                    other->position.x + other->size.x < position.x ||
                    other->position.y > position.y + size.y ||
                    other->position.y + other->size.y < position.y)
                return false;
            else
                return true;
        }
        glm::vec2 size;
        glm::vec2 position;

	std::function<void(void)> onCollision;
        bool overlaps = false;
        bool draw = false;
    };
}
#endif
