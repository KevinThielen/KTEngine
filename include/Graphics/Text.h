#ifndef KTE_TEXT_H
#define KTE_TEXT_H


#include <Graphics/ShaderManager.h>
#include <Components/Transformation.h>
#include <Graphics/Font.h>
#include <Graphics/Mesh.h>


namespace kte
{
    class Text : public Mesh
    {
    public:
        Text();

        virtual void bindVAO();
        void setFont(Font* f) { font = f; }
        void setString(std::string s);
        GLuint getTexture() { return font->getTexture(); }
        Transformation* getTransformation() { return &transformation; }

        void setColor(glm::vec4 color) { this->color = color; }
        glm::vec4 getColor() { return color; }
    private:
        glm::vec4 color;
        Font* font;
        std::string textString;
        Transformation transformation;
        GLuint vao;
        GLuint vbo;
        GLuint ibo;

    };
}

#endif