#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include <vector>
#include <map>
#include <memory>
#include <GameObject.h>
#include "ISystem.h"
#include "Components/MouseInputComponent.h"
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
			bool mouseDown = Input::isMouseDown();

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
						}
					}
					else if (!mouseDown && mouseInputComponent->isDown)
					{
						mouseInputComponent->isDown = false;

						if (trans->contains(mousePosition.x, mousePosition.y))
		  				   mouseInputComponent->onRelease();
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
			}

			if(dynamic_cast<kte::GameObjectRemovedMessage*>(message))
			{
				GameObjectRemovedMessage* gameObjectRemovedMessage = dynamic_cast<kte::GameObjectRemovedMessage*>(message);

				if(mouseInputComponents.count(gameObjectRemovedMessage->gameObjectId))
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
		std::map<unsigned int, std::vector<MouseInputComponent*>> mouseInputComponents;
		std::map<unsigned int, TransformationComponent*> transformations;
    };
}

#endif