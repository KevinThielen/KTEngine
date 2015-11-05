#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include <vector>
#include <memory>

#include "ISystem.h"
#include "Components/SpriteComponent.h"
#include "Components/TransformationComponent.h"
#include "Components/TextComponent.h"
#include "Components/BoxCollider.h"
#include "Messages/ComponentAddedMessage.h"
#include "Messages/ContextChange.h"
#include "Messages/GameObjectRemovedMessage.h"
#include "Graphics/RenderTechnique.h"
#include <Graphics/TextTechnique.h>
#include "Graphics/Text.h"
#include <Graphics/PostProcessing.h>

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
   //         textTechnique->render(text);
        }

        static bool checkGLError(std::string message = "") 
	{
	    GLenum error = glGetError();
	    bool errorFound = false;
	    while(error != GL_NO_ERROR)
	    {
		std::cout<<"GL Error: "<<message<<"("<<std::to_string(error)<< "): "<<glewGetErrorString(error)<<std::endl;
		error = glGetError();
		errorFound = true;
	    }
	    
	    return errorFound;
	}
    private:
        std::map<unsigned int, TransformationComponent*> transformationComponents;
        std::map<unsigned int, SpriteComponent*> spriteComponents;
        std::vector<BoxCollider*> boxColliders;

        std::map<SpriteComponent*, TransformationComponent*> spritesToRender;
        bool componentsChanged = true;
	
	Resources* resources;
        //render Techniques
        std::vector<std::unique_ptr<RenderTechnique>> renderTechniques;

        std::unique_ptr<TextTechnique> textTechnique;
        std::map<unsigned int, TextComponent*> textComponents;
	std::map<unsigned int, Text> textsToRender;
	PostProcessing postProcessing;
    };
}

#endif