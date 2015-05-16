#ifndef KTE_GAMEOBJECT_REMOVED_MESSAGE_H
#define KTE_GAMEOBJECT_REMOVED_MESSAGE_H

#include "Message.h"
namespace kte
{
    struct IComponent;

    struct GameObjectRemovedMessage : public Message
    {
        unsigned int gameObjectId;
    };
}
#endif