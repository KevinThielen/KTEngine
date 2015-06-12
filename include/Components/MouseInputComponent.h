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
            onMouseOver = [] () {std::cout<<"hover"<<std::endl;};
            onMouseLeave = [] () {std::cout<<"leave"<<std::endl;};
        }

        bool isDown = false;
	bool isHovering = false;
	
        std::function<void(void)> onClick;
        std::function<void(void)> onMouseOver;
        std::function<void(void)> onMouseLeave;
    };
}
#endif
