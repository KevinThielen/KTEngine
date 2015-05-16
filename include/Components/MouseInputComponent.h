#ifndef KTE_MOUSE_INPUT_COMPONENT_H
#define KTE_MOUSE_INPUT_COMPONENT_H

#include <glm/glm.hpp>
#include "IComponent.h"
#include <algorithm> //std::function
#include <iostream>

namespace kte
{
    struct MouseInputComponent : public IComponent
    {
        MouseInputComponent(unsigned int gameObjectId) : IComponent(gameObjectId)
        {
            onClick = [] () {std::cout<<"click"<<std::endl;};
        }

        bool isDown = false;
        std::function<void(void)> onClick;
    };
}
#endif
