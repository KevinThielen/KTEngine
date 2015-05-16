#include "Graphics/ShaderManager.h"
#include "GameObject.h"
#include "Components/SpriteComponent.h"
#include "Graphics/Quad.h"
#include "Graphics/SpriteTechnique.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <Graphics/Texture.h>
#include "Graphics/RenderTechnique.h"
#include "Components/Camera.h"

namespace kte
{
    SpriteTechnique::SpriteTechnique() : RenderTechnique("SpriteTechnique")
    {
        numberOfRenderpasses = 1;
    }

    bool SpriteTechnique::init()
    {
        ShaderManager* shaderManager = ShaderManager::instance();
        if(!shaderManager->getShaderProgram("SpriteShader"))
        {
            if(!shaderManager->shaderProgramFromFile("SpriteShader", "SpriteShader.vs", "SpriteShader.fs"))
                return false;
        }

        programId = shaderManager->getShaderProgram("SpriteShader");

        quad = &kte::Geometry::quad;

        resources.loadTextureFromFile("default.png");
        defaultTexture = resources.getTexture("default.png")->getTexture();

        return true;
    }
    void SpriteTechnique::use()
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
    void SpriteTechnique::render(std::map<SpriteComponent*, TransformationComponent*> spritesToRender)
    {
        //remove old cached sprite
        cachedSprites.clear();

        glUseProgram(programId);


        std::map<unsigned int, std::map<SpriteComponent*, TransformationComponent*>> spritesSortedByLayer;
        for(auto sprite : spritesToRender)
        {
            SpriteComponent* spriteComponent = sprite.first;
            TransformationComponent* transComp = sprite.second;

            spritesSortedByLayer[spriteComponent->layer][spriteComponent] = transComp;
        }

        for(auto layerSprites : spritesSortedByLayer)
        {
            std::map<kte::Texture *, std::map<SpriteComponent *, TransformationComponent *>> spritesSortedByTexture;

            kte::Camera *mainCam = Camera::getMainCamera();
            glm::mat4 viewMatrix;
            if (mainCam)
                viewMatrix = mainCam->getMatrix();

            //one draw call for each tetxure
            for (auto sprite : layerSprites.second)
            {
                SpriteComponent *spriteComponent = sprite.first;
                TransformationComponent *transComp = sprite.second;

                    spritesSortedByTexture[spriteComponent->texture][spriteComponent] = transComp;
            }

            for (auto sortedSprites : spritesSortedByTexture)
            {
                //single drawCall
                quad->bindVAO();

                std::vector<glm::mat4> mvps;
                std::vector<glm::vec4> colors;
                std::vector<glm::vec4> uvs;

                Texture *texture = sortedSprites.first;

                if (texture)
                {
                    GLint textureLoc = glGetUniformLocation(programId, "texture");
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, texture->getTexture());
                    glUniform1i(textureLoc, 0);
                }
                else
                {
                    GLint textureLoc = glGetUniformLocation(programId, "texture");
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, defaultTexture);
                    glUniform1i(textureLoc, 0);
                }

                RenderData cachedSprite;

                for (auto sprite : sortedSprites.second)
                {
                    TransformationComponent *transformationComponent = sprite.second;
                    SpriteComponent *spriteComponent = sprite.first;

                    const float z = spriteComponent->layer * 0.01f;
                    glm::vec3 position(transformationComponent->x, transformationComponent->y, z);

                    glm::vec3 rotation(transformationComponent->xRotation, transformationComponent->yRotation, transformationComponent->zRotation);

                    glm::vec3 spriteOffset(spriteComponent->spriteOffsetX, spriteComponent->spriteOffsetY, 0);

                    glm::vec3 size(transformationComponent->width, transformationComponent->height, 1);



                    kte::TransformationComponent *parentTransform = transformationComponent->parentTransform;
                    while (parentTransform != nullptr)
                    {
                        position += glm::vec3(parentTransform->x, parentTransform->y, 0);
                        parentTransform = parentTransform->parentTransform;
                    }
                    glm::vec3 finalPosition = position + spriteOffset;


                    glm::vec4 textureRectangle = spriteComponent->textureRectangle;
                    if(spriteComponent->mirrored)
                    {
                        textureRectangle.x += textureRectangle.z;
                        textureRectangle.z *= -1;
                    }
                    glm::mat4 matrix;
                    matrix = glm::translate(matrix, size / 2.0f + finalPosition);
                    matrix = glm::rotate(matrix, rotation.x, glm::vec3(1, 0, 0));
                    matrix = glm::rotate(matrix, rotation.y, glm::vec3(0, 1, 0));
                    matrix = glm::rotate(matrix, rotation.z, glm::vec3(0, 0, 1));
                    matrix = glm::translate(matrix, (-size / 2.0f));
                    matrix = glm::scale(matrix, size);

                    mvps.push_back(viewMatrix * matrix);
                    colors.push_back(spriteComponent->color);
                    uvs.push_back(textureRectangle);
                }

                glBindBuffer(GL_ARRAY_BUFFER, quad->getMVP());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * sortedSprites.second.size(), &mvps[0], GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, quad->getCOLOR());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * sortedSprites.second.size(), &colors[0], GL_DYNAMIC_DRAW);

                glBindBuffer(GL_ARRAY_BUFFER, quad->getUV());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * sortedSprites.second.size(), &uvs[0], GL_DYNAMIC_DRAW);


                glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad->getNumberOfIndices(), sortedSprites.second.size());

                //save for later use
                cachedSprite.mvps = mvps;
                cachedSprite.colors = colors;
                cachedSprite.uvs = uvs;
                cachedSprite.texture = texture;

                cachedSprites.push_back(cachedSprite);

                glBindTexture(GL_TEXTURE_2D, 0);
                glBindVertexArray(0);

            }
        }
    }

    void SpriteTechnique::renderCached()
    {
       for(auto sprite : cachedSprites)
       {
           quad->bindVAO();

           if (sprite.texture)
           {
               GLint textureLoc = glGetUniformLocation(programId, "texture");
               glActiveTexture(GL_TEXTURE0);
               glBindTexture(GL_TEXTURE_2D, sprite.texture->getTexture());
               glUniform1i(textureLoc, 0);
           }
           else
           {
               GLint textureLoc = glGetUniformLocation(programId, "texture");
               glActiveTexture(GL_TEXTURE0);
               glBindTexture(GL_TEXTURE_2D, defaultTexture);
               glUniform1i(textureLoc, 0);
           }

           glBindBuffer(GL_ARRAY_BUFFER, quad->getMVP());
           glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * sprite.mvps.size(), &sprite.mvps[0], GL_DYNAMIC_DRAW);

           glBindBuffer(GL_ARRAY_BUFFER, quad->getCOLOR());
           glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * sprite.mvps.size(), &sprite.colors[0], GL_DYNAMIC_DRAW);

           glBindBuffer(GL_ARRAY_BUFFER, quad->getUV());
           glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * sprite.mvps.size(), &sprite.uvs[0], GL_DYNAMIC_DRAW);


           glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, quad->getNumberOfIndices(), sprite.mvps.size());

           glBindTexture(GL_TEXTURE_2D, 0);
           glBindVertexArray(0);
       }
    }
}