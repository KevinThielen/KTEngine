#include <Graphics/ShaderManager.h>
#include <GameObject.h>
#include <Components/RenderComponent.h>
#include <Graphics/Mesh.h>
#include <Graphics/RenderTechniques/SpriteTechnique.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Components/Camera.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace kte
{
    SpriteTechnique::SpriteTechnique(std::string name) : RenderTechnique(name)
    {
        numberOfRenderpasses = 1;
        ShaderManager* shaderManager = ShaderManager::getInstance();
        programId = shaderManager->getShaderProgram("BasicShader");


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
    void SpriteTechnique::render(std::vector<GameObject*> gameObjects)
    {



        std::map<float, std::vector<GameObject>> sortedByZ;


        for(int i =0; i<gameObjects.size(); i++)
        {
            sortedByZ[gameObjects[i]->getTransformation()->getPosition().z].push_back(*gameObjects[i]);
        }
        for(auto iterator = sortedByZ.begin(); iterator != sortedByZ.end(); iterator++)
        {
            std::map<Texture *, std::vector<GameObject>> sortedByTexture;

            for (int i = 0; i < (sortedByZ[iterator->first]).size(); i++)
            {
                GameObject go = (sortedByZ[iterator->first])[i];
                RenderComponent *renderComp = go.getComponent<RenderComponent>();

                Texture *texture;
                texture = renderComp->getMaterial()->getTexture();
                sortedByTexture[texture].push_back(go);
            }


            for (auto meshIterator = sortedByTexture.begin(); meshIterator != sortedByTexture.end(); meshIterator++)
            {
                std::vector<GameObject> gameObjectsWithTexture = meshIterator->second;
                Mesh *mesh = gameObjectsWithTexture.front().addComponent<RenderComponent>()->getMesh();

                mesh->bindVAO();
                unsigned int numberOfInstaces = 0;
                std::vector<glm::mat4> mvps;
                std::vector<glm::vec4> colors;
                std::vector<GameObject> gameObjectsWithMesh = meshIterator->second;

                Texture *texture = meshIterator->first;

                GLint textureLoc = glGetUniformLocation(programId, "texture");
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, texture->getTexture());
                glUniform1i(textureLoc, 0);


                //  std::sort(sortedByZ.begin(), sortedByZ.end());


                for (auto goIterator = gameObjectsWithMesh.begin(); goIterator != gameObjectsWithMesh.end(); goIterator++)
                {
                    GameObject go = *goIterator;
                    Transformation trans = *go.getTransformation();
                    trans.setPosition(glm::vec3(trans.getPosition().x, trans.getPosition().y, 0.0f));
                    RenderComponent *renderComp = go.getComponent<RenderComponent>();
                    mvps.push_back(Camera::getMainCamera()->getMatrix() * trans.getMatrix());
                    colors.push_back(renderComp->getMaterial()->getColor());
                    numberOfInstaces++;
                }

                //single drawCall
                glBindBuffer(GL_ARRAY_BUFFER, mesh->getMVP());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * numberOfInstaces, &mvps[0], GL_DYNAMIC_DRAW);


                glBindBuffer(GL_ARRAY_BUFFER, mesh->getCOLOR());
                glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * numberOfInstaces, &colors[0], GL_DYNAMIC_DRAW);


                glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, mesh->getNumberOfIndices(), numberOfInstaces);
            }
        }


        glBindVertexArray(0);
    }
}