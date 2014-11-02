#include <Graphics/ShaderManager.h>
#include <GameObject.h>
#include <Components/RenderComponent.h>
#include <Graphics/Mesh.h>
#include <Graphics/RenderTechniques/FontTechnique.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Components/Camera.h>
#include <GLFW/glfw3.h>

#include <iostream>


namespace kte
{
    FontTechnique::FontTechnique(std::string name) : RenderTechnique(name)
    {
        numberOfRenderpasses = 1;
        ShaderManager* shaderManager = ShaderManager::getInstance();
        programId = shaderManager->getShaderProgram("FontShader");
    }

    void FontTechnique::use()
    {
        ShaderManager* shaderManager = ShaderManager::getInstance();
        glUseProgram(shaderManager->getShaderProgram("FontShader"));
        currentTexture = 0;
    }

    /**************************************
    * The technique gets a list of all gameObjets, using this technique
    * and orders them by their mesh. It will iterate through each mesh list
    * and batches them, before rendering them with a single draw call.
    *
    *
    ***************************************/
    void FontTechnique::render(std::vector<Text*> texts)
    {
        ShaderManager* shaderManager = ShaderManager::getInstance();
        for (unsigned int i = 0; i < texts.size(); i++)
        {
            Text* text = texts[i];
            glm::vec4 color = text->getColor();
            text->bindVAO();

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, text->getTexture());
                currentTexture = text->getTexture();


            glm::mat4 MVP = Camera::getMainCamera()->getMatrix() * text->getTransformation()->getMatrix();

            glUniformMatrix4fv(glGetUniformLocation(shaderManager->getShaderProgram("FontShader"), "MVP"), 1, GL_FALSE, &MVP[0][0]);
            glUniform4fv(glGetUniformLocation(shaderManager->getShaderProgram("FontShader"), "COLOR"), 1, &color[0]);


            glDrawElements(GL_TRIANGLES, text->getNumberOfIndices(), GL_UNSIGNED_SHORT, (void *) 0);

            glBindVertexArray(0);
        }
    }
}