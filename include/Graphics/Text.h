#ifndef KTE_TEXT_H
#define KTE_TEXT_H

#include <map>
#include <Graphics/Font.h>
#include <Graphics/Quad.h>

#include <glm/glm.hpp>

namespace kte
{
    class Text
    {
    public:
        void setFont(Font* f) { font = f; }
        void setString(std::string s);


        void setColor(glm::vec4 color) { this->color = color; }
        glm::vec4 getColor() { return color; }

        void setPosition(float x, float y) { position.x = x; position.y = y; }
        glm::vec2 getPosition() { return position; }

        glm::vec4 getTextureRectangle(char c) { return textureRectangles[c]; }
        glm::vec4 getRectangle(char c) { return rectangles[c]; }

        unsigned int getLength() { return length; }

        unsigned int getTexture() { return  font->getTexture(); }
    private:
//         Quad quad;
        glm::vec2 position;
        glm::vec2 size;
        glm::vec4 color;

        Font* font;
        unsigned int length;
        std::string textString;

        std::map<char, glm::vec4> textureRectangles;
        std::map<char, glm::vec4> rectangles;
    };
}

#endif