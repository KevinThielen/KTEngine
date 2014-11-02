#ifndef KTE_CLICKABLECOMPONENT_H
#define KTE_CLICKABLECOMPONENT_H

#include "IComponent.h"
namespace kte
{
    class ClickableComponent : public IComponent
    {
    public:
        ClickableComponent(unsigned int gameObjectId) : IComponent(gameObjectId)
        {

        }
    };

}

#endif