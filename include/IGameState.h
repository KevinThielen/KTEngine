#ifndef KTE_IGAMESTATE_H
#define KTE_IGAMESTATE_H

namespace kte
{
    class IGameState
    {
    public:
        virtual ~IGameState(){};
        virtual void update() = 0;
        virtual bool initialize() = 0;
        virtual void release() = 0;
    };
}

#endif