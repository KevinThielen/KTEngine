#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include <glm/glm.hpp>
#include "IComponent.h"
#include <vector>
namespace kte
{
    class Texture;
    struct TextComponent : public IComponent
    {
        TextComponent(unsigned int gameObjectId) : IComponent(gameObjectId)
        {

        }
        
       
        std::string renderTechnique = "TextTechnique";
        int layer = 1;
	std::string font = "";
	std::string text = "";
	
	
	float deltaY = 0.0f;
        float xOffset = 0;
        float yOffset = 0;
	
	 
        glm::vec4 color = glm::vec4(1,1,1,1);
	std::vector<glm::vec4> colors;
    };
}
#endif