#ifndef  KTE_ICOMPONENT_H
#define KTE_ICOMPONENT_H

/************************
* Component interface. A Gameobject contains a list of different components.
* components contains data only and are used by the system for different purposes, like
* rendering, physics, ect
*************************/

namespace kte
{
    struct IComponent
    {
        /*****************
        * A component need the gameObjectId, as a callback channel for several systems
        ******************/
        IComponent(unsigned int gameObjectId) : gameObjectId(gameObjectId)
        {
        }

        virtual ~IComponent()
        {

        }

        unsigned int gameObjectId = -1;
    };
}
#endif