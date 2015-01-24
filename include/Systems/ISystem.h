#ifndef KTE_ISYSTEM_H
#define KTE_ISYSTEM_H

#include <string>

namespace kte
{
    class ISystem
    {
    public:
        virtual bool init() {}
        virtual void update(float dt) = 0;
        virtual void receiveMessage(std::string message) {}


    };
}
#endif