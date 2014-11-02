#include <Graphics/ShaderManager.h>
#include <GameObject.h>
#include <Components/RenderComponent.h>
#include <Graphics/Mesh.h>
#include <Graphics/RenderTechniques/BasicTechnique.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Components/Camera.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace kte
{
    BasicTechnique::BasicTechnique(std::string name) : RenderTechnique(name)
    {
        numberOfRenderpasses = 1;
        ShaderManager* shaderManager = ShaderManager::getInstance();
        programId = shaderManager->getShaderProgram("BasicShader");


    }

    void BasicTechnique::use()
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
    void BasicTechnique::render(std::vector<GameObject*> gameObjects)
    {
        std::map<Texture*, std::vector<GameObject>> sortedByTexture;

        for(int i = 0; i<gameObjects.size(); i++)
        {
            GameObject* go = gameObjects[i];
            RenderComponent *renderComp = go->getComponent<RenderComponent>();

            Texture *texture;
            texture = renderComp->getMaterial()->getTexture();
            sortedByTexture[texture].push_back(*go);

        }

        for(auto meshIterator = sortedByTexture.begin(); meshIterator != sortedByTexture.end(); meshIterator++)
        {
            std::vector<GameObject>  gameObjectsWithTexture = meshIterator->second;
            Mesh* mesh = gameObjectsWithTexture.front().addComponent<RenderComponent>()->getMesh();

            mesh->bindVAO();
            unsigned int numberOfInstaces = 0;
            std::vector<glm::mat4> mvps;
            std::vector<glm::vec4> colors;
            std::vector<GameObject>  gameObjectsWithMesh = meshIterator->second;

            Texture* texture = meshIterator->first;
            for(auto goIterator = gameObjectsWithMesh.begin(); goIterator != gameObjectsWithMesh.end(); goIterator++)
            {
                GameObject go = *goIterator;
                Transformation* trans = go.getTransformation();
                RenderComponent* renderComp = go.getComponent<RenderComponent>();
                    mvps.push_back(Camera::getMainCamera()->getMatrix() * trans->getMatrix());
                    colors.push_back(renderComp->getMaterial()->getColor());
                    numberOfInstaces++;
            }

            //sort colors by alpha

            GLint textureLoc = glGetUniformLocation(programId, "texture");
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture->getTexture());
            glUniform1i(textureLoc, 0);
            //single drawCall
            glBindBuffer(GL_ARRAY_BUFFER, mesh->getMVP());
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4)*numberOfInstaces, &mvps[0], GL_DYNAMIC_DRAW);


            glBindBuffer(GL_ARRAY_BUFFER, mesh->getCOLOR());
            glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4)*numberOfInstaces, &colors[0], GL_DYNAMIC_DRAW);


            glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, mesh->getNumberOfIndices(), numberOfInstaces);
        }


        glBindVertexArray(0);
    }
}