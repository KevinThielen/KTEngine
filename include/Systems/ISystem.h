#ifndef KTE_ISYSTEM_H
#define KTE_ISYSTEM_H

#include <string>
#include "Messages/Message.h"


namespace kte
{
    class ISystem
    {
    public:
	virtual ~ISystem(){}
        virtual bool init() {return true;}
        virtual void update(float dt) = 0;
        virtual void receiveMessage(Message* message) {}
    };
}
#endif