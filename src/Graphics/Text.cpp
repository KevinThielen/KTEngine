#include <Graphics/Text.h>

namespace kte
{
    Text::Text()
    {
        numberOfIndices = 0;

    }
    void Text::setString(std::string s)
    {
        textString = s;

        ShaderManager* shaderManager = ShaderManager::getInstance();


        float xOffset = 0.0f;
        float yOffset = 0.0f;
        numberOfIndices = 0;

        std::vector<GLfloat> vertexData;
        std::vector<unsigned short> indices;

        unsigned short indicesOffset = 0;
        for (unsigned int i = 0; i < s.length(); i++)
        {
            char c = s[i];

            if (c == '\n')
            {
                xOffset = 0.0f;
                yOffset += font->getTextureHeight();
            }

            else
            {

                GlyphInformation g = font->getGlyp(c);
                //create fontSprite
                //TL
                vertexData.push_back(xOffset + g.bitmapLeft);
                vertexData.push_back(yOffset+ (font->getTextureHeight() - g.bitmapTop));
                vertexData.push_back(0.0f);
                vertexData.push_back(g.textureX);
                vertexData.push_back(0.0f);

                //TR
                vertexData.push_back(xOffset+ g.bitmapLeft+g.bitmapWidth);
                vertexData.push_back(yOffset + (font->getTextureHeight() - g.bitmapTop));
                vertexData.push_back(0.0f);
                vertexData.push_back(g.textureX + g.bitmapWidth / font->getTextureWidth());
                vertexData.push_back(0.0f);

                //BL
                vertexData.push_back(xOffset+g.bitmapLeft);
                vertexData.push_back(yOffset + font->getTextureHeight());
                vertexData.push_back(0.0f);
                vertexData.push_back(g.textureX);
                vertexData.push_back(1.0f);


                //BR
                vertexData.push_back(xOffset+ + g.bitmapLeft+g.bitmapWidth);
                vertexData.push_back(yOffset + font->getTextureHeight());
                vertexData.push_back(0.0f);
                vertexData.push_back(g.textureX + g.bitmapWidth/ font->getTextureWidth());
                vertexData.push_back(1.0f);

                indices.push_back(0 + indicesOffset);
                indices.push_back(1 + indicesOffset);
                indices.push_back(2 + indicesOffset);

                indices.push_back(2 + indicesOffset);
                indices.push_back(1 + indicesOffset);
                indices.push_back(3 + indicesOffset);

                indicesOffset += 4;

                xOffset += g.advanceX;
            }
        }

        numberOfIndices = indices.size();

        //create buffers
        glGenBuffers(1, &ibo);
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        //bind data to buffer
        glBindVertexArray(vao);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);

        //shader attributes
        glEnableVertexAttribArray(shaderManager->getAttribLocation("vertex"));
        glVertexAttribPointer(shaderManager->getAttribLocation("vertex"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);

        glEnableVertexAttribArray(shaderManager->getAttribLocation("uv"));
        glVertexAttribPointer(shaderManager->getAttribLocation("uv"), 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));


        //unbind vao
        glBindVertexArray(0);
    }

    void Text::bindVAO()
    {
        glBindVertexArray(vao);
    }
}