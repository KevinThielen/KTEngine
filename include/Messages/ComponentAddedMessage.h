#ifndef KTE_COMPONENT_ADDED_MESSAGE_H
#define KTE_COMPONENT_ADDED_MESSAGE_H

#include "Message.h"
namespace kte
{
    struct IComponent;

    struct ComponentAddedMessage : public Message
    {
        unsigned int gameObjectId;
        IComponent* addedComponent;
    };
}
#endif