#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include "ISystem.h"
#include "Components/SpriteComponent.h"

namespace kte
{
    class RenderSystem : public ISystem
    {
    public:
        RenderSystem() { }
        ~RenderSystem() { }

        virtual bool init();
        virtual void update(float dt);
        virtual void receiveMessage(std::string message);

    private:
        std::vector<SpriteComponent*> spriteComponents;

        //render Techniques
//        std::vector<SpriteComponent*> spriteComponents;

        //Textures
    };
}

#endif