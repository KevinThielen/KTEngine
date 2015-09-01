#ifndef KTE_KEY_INPUT_COMPONENT_H
#define KTE_KEY_INPUT_COMPONENT_H

#include <glm/glm.hpp>
#include "IComponent.h"
#include <algorithm> //std::function
#include <iostream>
#include <Input.h>

namespace kte
{
    struct KeyInputComponent : public IComponent
    {
        KeyInputComponent(unsigned int gameObjectId) : IComponent(gameObjectId)
        {
        }

        void setOnKeyDown(int key, std::function<void(void)> onDown)
	{
	    keyStates[key] = Input::isKeyDown(key);
	    if(!onKeyUp.count(key)) 
		onKeyUp[key] = [](){};
	    onKeyDown[key] = onDown;
	}
        void setOnKeyUp(int key, std::function<void(void)> onUp)
	{
	    keyStates[key] = Input::isKeyDown(key);
	    if(!onKeyDown.count(key)) 
		onKeyDown[key] = [](){};
	    onKeyUp[key] = onUp;
	}
	
        std::map<int, bool> keyStates;
	std::map<int, std::function<void(void)>> onKeyDown;
	std::map<int, std::function<void(void)>> onKeyUp;
    };
}
#endif
