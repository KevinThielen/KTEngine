#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include <memory>

#include "ISystem.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformationComponent.h"
#include "Components/BoxCollider.h"
#include "Messages/ComponentAddedMessage.h"
#include "Messages/GameObjectRemovedMessage.h"
#include "Graphics/RenderTechnique.h"
#include <Graphics/TextTechnique.h>

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

        void displayText(Text t)
        {
            textTechnique->render(t);
        }

        void displayText(std::vector<Text> text)
        {
            textTechnique->render(text);
        }

    private:
        std::map<unsigned int, TransformationComponent*> transformationComponents;
        std::map<unsigned int, SpriteComponent*> spriteComponents;
        std::vector<BoxCollider*> boxColliders;

        std::map<SpriteComponent*, TransformationComponent*> spritesToRender;
        bool componentsChanged = true;
        //render Techniques
        std::vector<std::unique_ptr<RenderTechnique>> renderTechniques;

        std::unique_ptr<TextTechnique> textTechnique;
    };
}

#endif