#ifndef KTE_TEXT_H
#define KTE_TEXT_H

#include <map>
#include <vector>
#include <Graphics/FontTexture.h>
#include <Graphics/Quad.h>
#include <iostream>
#include <glm/glm.hpp>

namespace kte
{
    class Text
    {
    public:
        void setFont(FontTexture* f)
	{ 
	    size = glm::vec2(1,1);
	    fontTexture = f; 
	}
	
        void setString(std::string s);
	
        void setColor(glm::vec4 color) { this->color = color; colors.clear(); colors.push_back(color); }
	glm::vec4 getColor(unsigned int index = 0) {  if(!colors.size()) return glm::vec4(0,0,0,1); else  return colors[index%colors.size()]; }
        void addColor(glm::vec4 color) { colors.push_back(color); }
        void setColors(std::vector<glm::vec4> colorList) { colors = colorList; }
        
        void setPosition(float x, float y) { position.x = x; position.y = y; }
        glm::vec2 getPosition() { return position; }

        glm::vec4 getTextureRectangle(unsigned int c) { return textureRectangles[c]; }
        glm::vec4 getRectangle(unsigned int c) { return rectangles[c]; }

        unsigned int getLength() { return length; }

        GLuint getTexture() { return  fontTexture->getTexture(); }
        void setSize(float x, float y) { size = glm::vec2(x,y); }
	glm::vec2 getSize() { return size; }
	float getDeltaY() { return deltaY; }
	
    private:
        glm::vec2 position;
        glm::vec2 size;
        glm::vec4 color;

        FontTexture* fontTexture;
	
	float deltaY;
        unsigned int length;
        std::string textString;

        std::map<unsigned int, glm::vec4> textureRectangles;
        std::map<unsigned int, glm::vec4> rectangles;
        
	
	std::vector<glm::vec4> colors;
    };
}

#endif