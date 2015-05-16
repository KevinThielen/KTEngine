#ifndef KTE_ANIMATION_SYSTEM_H
#define KTE_ANIMATION_SYSTEM_H

#include <vector>
#include <memory>
#include <Resources.h>
#include "ISystem.h"
#include <Components/SpriteComponent.h>
#include <Components/Animator.h>
#include "Messages/ComponentAddedMessage.h"
#include "Messages/GameObjectRemovedMessage.h"

namespace kte
{
    class AnimationSystem : public ISystem
    {
    public:
        AnimationSystem(Resources* resources):resources(resources) { }
        ~AnimationSystem() { }

        virtual bool init();
        virtual void update(float dt);
        virtual void receiveMessage(Message* message);
        void loadAnimation(Animation* animation);

    private:
        std::map<unsigned int, SpriteComponent*> spriteComponents;
        std::map<unsigned int, Animator*> animators;
        Resources* resources = nullptr;
    };
}

#endif