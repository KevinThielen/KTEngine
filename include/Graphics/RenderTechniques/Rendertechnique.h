#ifndef KTE_RENDERTECHNIQUE_H
#define KTE_RENDERTECHNIQUE_H

#include <GL/glew.h>
#include <vector>

#include <GameObject.h>
/*********************
* The Rendertechnique creates a shader program
* from the Shaders passed to the constructor
* The renderer calls the use method with the matching render pass argument
*********************/


class Mesh;
namespace kte
{
    class RenderTechnique
    {
    public:
        /******************
        * Use the Rendertechnique at the passed renderPass
        *******************/
        RenderTechnique(std::string name) : name(name){}
        virtual ~RenderTechnique(){}
        virtual void use() = 0;
        virtual void render(std::vector<GameObject*> gameObjects) = 0;
        unsigned int getNumberOfRenderpasses() { return numberOfRenderpasses; }

        std::string getName() { return name; }
        void setName(std::string name) { this->name = name; }
    protected:
        unsigned int numberOfRenderpasses = 1;
        std::string name;

    };
}

#endif