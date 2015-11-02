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

	   position = glm::vec2(0,0);
           setViewMatrix(left, right, bottom, top);
        }

        glm::mat4 getMatrix() { return projectionMatrix * viewMatrix; }

        void setViewMatrix(float left, float right, float bottom, float top, float nearPlane = -0.01f, float farPlane = -100.0f)
        {
            this->left = left;
            this->right = right;
            this->bottom = bottom;
            this->top = top;
            this->nearPlane = nearPlane;
	    this->farPlane = farPlane;
	    
	    viewMatrix = glm::ortho(left, right, bottom, top, nearPlane, farPlane);
        }
        
    
	
        void move(float dx, float dy) 
	{
	    position.x += dx;
	    position.y += dy;
	    
	    updateMatrix();
	}
  
        void updateMatrix()
	{
	    viewMatrix = glm::ortho(left+position.x, right+position.x, bottom+position.y, top+position.y, nearPlane, farPlane);
	}
	
	glm::vec2 getPosition() { return position; }
	glm::vec2 getResolution() { return glm::vec2(right, bottom); }
	
        static void setMainCamera(Camera* camera) { Camera::mainCamera = camera; }
        static Camera* getMainCamera() { return mainCamera; }

        
    private:
        static Camera* mainCamera;

        glm::mat4 projectionMatrix;
        glm::mat4 viewMatrix;
	glm::vec2 position;
	
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