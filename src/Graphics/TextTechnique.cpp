#define GLM_FORCE_RADIANS
#include "Graphics/ShaderManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Graphics/RenderTechnique.h"
#include "Components/Camera.h"
#include "Graphics/TextTechnique.h"

namespace kte
{
    TextTechnique::TextTechnique() : RenderTechnique("TextTechnique")
    {
        numberOfRenderpasses = 1;
    }

    bool TextTechnique::init()
    {
        ShaderManager* shaderManager = ShaderManager::instance();
        if(!shaderManager->getShaderProgram("TextShader"))
        {
            if(!shaderManager->shaderProgramFromFile("TextShader", "TextShader.vs", "TextShader.fs"))
                return false;
        }

        programId = shaderManager->getShaderProgram("TextShader");

        quad = &kte::Geometry::quad;


        return true;
    }
    void TextTechnique::use()
    {
        glUseProgram(programId);
    }

    /**************************************
    * The technique gets a list of all gameObjets, using this technique
    * and orders them by their mesh. It will iterate through each mesh list
    * and batches them, before rendering them with a single draw call.
    *
    *
    ***************************************/
    void TextTechnique::render(std::vector<Text> texts)
    {

        glUseProgram(programId);

       std::map<unsigned int, std::vector<Text>> sortedByFont;

        kte::Camera *mainCam = Camera::getMainCamera();
        glm::mat4 viewMatrix;
        if (mainCam)
            viewMatrix = mainCam->getMatrix();

        for(auto text : texts)
        {
            sortedByFont[text.getTexture()].push_back(text);
        }

            for (auto text : sortedByFont)
            {
                //single drawCall
                quad->bindVAO();

                std::vector<glm::mat4> mvps;
                std::vector<glm::vec4> colors;
                std::vector<glm::vec4> uvs;



                    GLint textureLoc = glGetUniformLocation(programId, "texture");
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, text.first);
                    glUniform1i(textureLoc, 0);



                for (auto t : text.second)
                {
                    //for each character in text
                    for(unsigned int i = 0; i<t.getLength(); i++)
                    {
                        glm::vec4 rectangle = t.getRectangle(i);
                        glm::vec4 textureRectangle = t.getTextureRectangle(i);



                        glm::vec3 position(rectangle.x, rectangle.y, 1);

                        glm::vec3 size(rectangle.z, rectangle.a, 1);


                        glm::vec3 finalPosition = position;
			finalPosition.x += t.getPosition().x;
			finalPosition.y += t.getPosition().y;


                        glm::mat4 matrix;
                        matrix = glm::translate(matrix, size / 2.0f + finalPosition);
                        matrix = glm::translate(matrix, (-size / 2.0f));
                        matrix = glm::scale(matrix, size);

                        mvps.push_back(viewMatrix * matrix);
                        colors.push_back(t.getColor());
                        uvs.push_back(textureRectangle);
                    }


                }

                glBindBuffer(GL_ARRAY_BUFFER, quad->getMVP());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * mvps.size(), &mvps[0], GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, quad->getCOLOR());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * colors.size(), &colors[0], GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, quad->getUV());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * uvs.size(), &uvs[0], GL_DYNAMIC_DRAW);


                glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad->getNumberOfIndices(), uvs.size());


                glBindTexture(GL_TEXTURE_2D, 0);
                glBindVertexArray(0);

            }
        }


        void TextTechnique::render(Text text)
        {
            glUseProgram(programId);

            std::map<unsigned int, std::vector<Text>> sortedByFont;

            kte::Camera *mainCam = Camera::getMainCamera();
            glm::mat4 viewMatrix;
            if (mainCam)
                viewMatrix = mainCam->getMatrix();

                //single drawCall
                quad->bindVAO();

                std::vector<glm::mat4> mvps;
                std::vector<glm::vec4> colors;
                std::vector<glm::vec4> uvs;


                GLint textureLoc = glGetUniformLocation(programId, "texture");
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, text.getTexture());
                glUniform1i(textureLoc, 0);



                    //for each character in text
                    for(unsigned int i = 0; i<text.getLength(); i++)
                    {
                        glm::vec4 rectangle = text.getRectangle(i);
                        glm::vec4 textureRectangle = text.getTextureRectangle(i);


                        // const float z = spriteComponent->layer * 0.01f;

                        glm::vec3 position(rectangle.x, rectangle.y, 1);

                        // glm::vec3 rotation(transformationComponent->xRotation, transformationComponent->yRotation, transformationComponent->zRotation);

                        //glm::vec3 spriteOffset(spriteComponent->spriteOffsetX, spriteComponent->spriteOffsetY, 0);

                        glm::vec3 size(rectangle.z, rectangle.a, 1);


                        glm::vec3 finalPosition = position;
			finalPosition.x += text.getPosition().x;
			finalPosition.y += text.getPosition().y;



                        glm::mat4 matrix;
                        matrix = glm::translate(matrix, size / 2.0f + finalPosition);

                        matrix = glm::translate(matrix, (-size / 2.0f));
                        matrix = glm::scale(matrix, size);

                        mvps.push_back(viewMatrix * matrix);
                        colors.push_back(text.getColor());
                        uvs.push_back(textureRectangle);
                    }




                glBindBuffer(GL_ARRAY_BUFFER, quad->getMVP());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * mvps.size(), &mvps[0], GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, quad->getCOLOR());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * colors.size(), &colors[0], GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, quad->getUV());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * uvs.size(), &uvs[0], GL_DYNAMIC_DRAW);


                glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad->getNumberOfIndices(), uvs.size());


                glBindTexture(GL_TEXTURE_2D, 0);
                glBindVertexArray(0);

            }

}