#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <vector>
#include <map>
#include <memory>
#include <GameObject.h>
#include "ISystem.h"
#include "Components/MouseInputComponent.h"
#include "Components/KeyInputComponent.h"
#include "Messages/ComponentAddedMessage.h"
#include "Input.h"

namespace kte
{
    class InputSystem : public ISystem
    {
    public:
        InputSystem() { }
        ~InputSystem() { }

        virtual bool init(){ return true; }

		virtual void update(float dt)
		{
			glm::vec2 mousePosition = Input::getMousePosition();
			glm::vec2 deltaMousePosition = mousePosition - lastMousePosition;
			lastMousePosition = mousePosition;
			
			bool mouseMoved = (deltaMousePosition.x != 0 || deltaMousePosition.y != 0) ? true : false;
			bool mouseDown = Input::isMouseDown();

			
			for(auto& comps : keyInputComponents)
			{
			    
			    for(auto& comp : comps.second)
			    {
				if(comp->isActive)
				{
				    kte::KeyInputComponent* keyInputComponent = comp;
				    for(auto& keyState : keyInputComponent->keyStates)
				    {	
					bool newState = Input::isKeyDown(keyState.first);
					
					if(keyState.second != newState)
					{
					    keyState.second = newState;
					    
					    if(!newState)
					    {
						std::cout<<"key Up Once"<<std::endl;
						keyInputComponent->onKeyUp[keyState.first]();
					    }
					    else 
					    {
						std::cout<<"key Down Once"<<std::endl;
						keyInputComponent->onKeyDown[keyState.first]();
					    }
					    
					}
				    }
				}
			    }
			}
			for(auto& mouseInputComponentPair : mouseInputComponents)
			{
				for(auto& mouseInputComponent : mouseInputComponentPair.second)
				{
				    if(mouseInputComponent->isActive)
				    {
					TransformationComponent* trans = transformations[mouseInputComponent->gameObjectId];
					
					//onClick
					if (mouseDown && !mouseInputComponent->isDown)
					{
						if (trans->contains(mousePosition.x, mousePosition.y))
						{	mouseInputComponent->isDown = true;
							mouseInputComponent->onClick();
							mouseInputComponent->isDragged = true;
				
						}
					}
					else if (!mouseDown && mouseInputComponent->isDown)
					{
						mouseInputComponent->isDown = false;

						if (trans->contains(mousePosition.x, mousePosition.y))
		  				   mouseInputComponent->onRelease();
						
						mouseInputComponent->isDragged = false;
					}
					
					//onHover
					if(!mouseInputComponent->isHovering && trans->contains(mousePosition.x, mousePosition.y))
					{
					    mouseInputComponent->isHovering = true;
					    mouseInputComponent->onMouseOver();
					}
					else if(!trans->contains(mousePosition.x, mousePosition.y))
					{
					    if(mouseInputComponent->isHovering)
						mouseInputComponent->onMouseLeave();
					    
					    mouseInputComponent->isHovering = false;
					}
					//onMouseMove
					if(mouseMoved)
					{
					    mouseInputComponent->onMouseMove(deltaMousePosition.x, deltaMousePosition.y);
					    if(mouseInputComponent->isDragged)
						mouseInputComponent->onDrag(deltaMousePosition.x, deltaMousePosition.y);
					    
					    if (!trans->contains(mousePosition.x, mousePosition.y))
						mouseInputComponent->isDragged = false;
			
					}
					
				    }
				}
			}
		}

        virtual void receiveMessage(Message* message)
		{
			if(dynamic_cast<ComponentAddedMessage*>(message))
			{
				ComponentAddedMessage* componentAddedMessage = dynamic_cast<ComponentAddedMessage*>(message);

				if(dynamic_cast<TransformationComponent*>(componentAddedMessage->addedComponent))
				{
					transformations[componentAddedMessage->gameObjectId] = dynamic_cast<TransformationComponent*>(componentAddedMessage->addedComponent);
				}
				else if(dynamic_cast<MouseInputComponent*>(componentAddedMessage->addedComponent))
				{
					mouseInputComponents[componentAddedMessage->gameObjectId].push_back(dynamic_cast<MouseInputComponent*>(componentAddedMessage->addedComponent));
				}
				else if(dynamic_cast<KeyInputComponent*>(componentAddedMessage->addedComponent))
				{
					keyInputComponents[componentAddedMessage->gameObjectId].push_back(dynamic_cast<KeyInputComponent*>(componentAddedMessage->addedComponent));
				}
			}

			if(dynamic_cast<kte::GameObjectRemovedMessage*>(message))
			{
				GameObjectRemovedMessage* gameObjectRemovedMessage = dynamic_cast<kte::GameObjectRemovedMessage*>(message);

				if(mouseInputComponents.count(gameObjectRemovedMessage->gameObjectId))
				{
					mouseInputComponents[gameObjectRemovedMessage->gameObjectId].clear();
				}
				if(keyInputComponents.count(gameObjectRemovedMessage->gameObjectId))
				{
					mouseInputComponents[gameObjectRemovedMessage->gameObjectId].clear();
				}
				if(transformations.count(gameObjectRemovedMessage->gameObjectId))
				{
					transformations.erase(gameObjectRemovedMessage->gameObjectId);
				}
			}
		}

    private:
		std::map<unsigned int, std::vector<KeyInputComponent*>> keyInputComponents;
		std::map<unsigned int, std::vector<MouseInputComponent*>> mouseInputComponents;
		std::map<unsigned int, TransformationComponent*> transformations;
		
		glm::vec2 lastMousePosition;
    };
}

#endif