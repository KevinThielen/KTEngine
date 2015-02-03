#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Graphics/Quad.h"
#include "Graphics/ShaderManager.h"
#include <iostream>

namespace kte
{
    GLuint Mesh::mvp = 0;
    GLuint Mesh::color = 0;

    Quad::Quad()
    {


    }

    bool Quad::init()
    {
        ShaderManager* shaderManager = ShaderManager::instance();
        GLfloat vertexData[] =
                {
                        0.0f, 1.0f, 0.0f, 0.0f, 1.0f,   //TL
                        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,   //TR
                        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,   //BL
                        1.0f, 0.0f, 0.0f, 1.0f, 0.0f,   //BR
                };

        //create buffers
        glGenVertexArrays(1, &vao);

        glGenBuffers(1, &vbo);


        //bind data to buffer
        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

        //shader attributes
        glEnableVertexAttribArray(shaderManager->getAttribLocation("vertex"));
        glVertexAttribPointer(shaderManager->getAttribLocation("vertex"), 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);

        glEnableVertexAttribArray(shaderManager->getAttribLocation("uv"));
        glVertexAttribPointer(shaderManager->getAttribLocation("uv"), 2, GL_FLOAT, GL_TRUE, 5 * sizeof(GLfloat), (const GLvoid *) (3 * sizeof(GLfloat)));



        glGenBuffers(1, &uvVbo);
        glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
        glEnableVertexAttribArray(shaderManager->getAttribLocation("textureRectangle"));
        glVertexAttribPointer(shaderManager->getAttribLocation("textureRectangle"), 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), NULL);
        glVertexAttribDivisor(shaderManager->getAttribLocation("textureRectangle"), 1);

        glGenBuffers(1, &color);
        glBindBuffer(GL_ARRAY_BUFFER, color);
        glEnableVertexAttribArray(shaderManager->getAttribLocation("color"));
        glVertexAttribPointer(shaderManager->getAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), NULL);
        glVertexAttribDivisor(shaderManager->getAttribLocation("color"), 1);


        glGenBuffers(1, &mvp);
        glBindBuffer(GL_ARRAY_BUFFER, mvp);

        for (unsigned int i = 0; i < 4; i++)
        {
            glEnableVertexAttribArray(shaderManager->getAttribLocation("MVP") + i);
            glVertexAttribPointer(shaderManager->getAttribLocation("MVP") + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
                    (const GLvoid *) (sizeof(GLfloat) * i * 4));
            glVertexAttribDivisor(shaderManager->getAttribLocation("MVP") + i, 1);
        }

        //unbind vao
        glBindVertexArray(0);

        numberOfIndices = 4;

        return true;
    }
}