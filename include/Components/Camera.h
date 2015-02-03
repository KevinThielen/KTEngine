#ifndef KTE_CAMERA_H
#define KTE_CAMERA_H


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <Components/IComponent.h>

namespace kte
{
    struct Camera : public IComponent
    {
    public:
        Camera(unsigned int gameObjectId) : IComponent(gameObjectId)
        {
            if(mainCamera == nullptr)
                mainCamera = this;

            viewMatrix = glm::ortho(left, right, bottom, top);
        }

        glm::mat4 getMatrix() { return projectionMatrix * viewMatrix; }

        void setViewMatrix(float left, float right, float bottom, float top)
        {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;

            viewMatrix = glm::ortho(left, right, bottom, top);
        }
        static void setMainCamera(Camera* camera) { Camera::mainCamera = camera; }
        static Camera* getMainCamera() { return mainCamera; }

    private:
        static Camera* mainCamera;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;

        float 	fieldOfView = 45.0f,
                aspectRatio = 4.0f / 3.0f,
                nearPlane = 0.01f,
                farPlane = 100.0f;

        float left = 0.0f,
                right = 800.0f,
                top = 0.0f,
                bottom = 600.0f;
    };

}


#endif