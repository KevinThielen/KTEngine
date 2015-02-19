#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include <memory>
#include "ISystem.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformationComponent.h"
#include "Components/BoxCollider.h"
#include "Messages/ComponentAddedMessage.h"
#include "Graphics/RenderTechnique.h"

namespace kte
{
    class RenderSystem : public ISystem
    {
    public:
        RenderSystem() { }
        ~RenderSystem() { }

        virtual bool init();
        virtual void update(float dt);
        virtual void receiveMessage(Message* message);

    private:
        std::vector<SpriteComponent*> spriteComponents;
        std::vector<TransformationComponent*> transformationComponents;
        std::vector<BoxCollider*> boxColliders;

        //render Techniques
        std::vector<std::unique_ptr<RenderTechnique>> renderTechniques;
    };
}

#endif