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
            onRelease = [] () {std::cout<<"release"<<std::endl;};
            onMouseMove = [] (float x, float y) {};
            onDrag = [] (float x, float y) {};
        }

        bool isDown = false;
	bool isHovering = false;
	bool isDragged = false;
	
        std::function<void(void)> onClick;
        std::function<void(void)> onRelease;
        std::function<void(void)> onMouseOver;
        std::function<void(void)> onMouseLeave;
        std::function<void(float deltaX, float deltaY)> onMouseMove;
        std::function<void(float deltaX, float deltaY)> onDrag;
    };
}
#endif
