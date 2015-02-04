#ifndef KTE_COLLISION_SYSTEM_H
#define KTE_COLLISION_SYSTEM_H

#include <vector>
#include <memory>
#include "ISystem.h"
#include "Components/TransformationComponent.h"
#include "Components/MovementComponent.h"
#include "Components/BoxCollider.h"
#include "Messages/ComponentAddedMessage.h"

namespace kte
{
    class MovementSystem : public ISystem
    {
    public:
        MovementSystem() { }
        ~MovementSystem() { }

        virtual bool init();
        virtual void update(__attribute__((unused)) float dt);
        virtual void receiveMessage(Message* message);

    private:
        std::vector<MovementComponent*> movementComponents;
        std::vector<TransformationComponent*> transformationComponents;
        std::vector<BoxCollider*> boxColliders;
    };
}

#endif