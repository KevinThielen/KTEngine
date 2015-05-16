#ifndef KTE_RENDERTECHNIQUE_H
#define KTE_RENDERTECHNIQUE_H

#include <map>
#include <GL/glew.h>
#include "Components/TransformationComponent.h"
#include "Components/SpriteComponent.h"

namespace kte
{
    class GameObject;
    class RenderTechnique
    {
    public:
        /******************
        * Use the Rendertechnique at the passed renderPass
        *******************/
        RenderTechnique(std::string name) : name(name){}
        virtual ~RenderTechnique(){}
        virtual void use() = 0;
        virtual bool init() = 0;
        virtual void render(std::map<SpriteComponent*, TransformationComponent*> spritesToRender){}
        virtual void renderCached(){}
        unsigned int getNumberOfRenderpasses() { return numberOfRenderpasses; }

        std::string getName() { return name; }
        void setName(std::string name) { this->name = name; }

    protected:
        unsigned int numberOfRenderpasses = 1;
        std::string name;
    };
}

#endif