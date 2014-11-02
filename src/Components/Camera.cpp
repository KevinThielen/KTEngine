#include "Components/Camera.h"

namespace kte
{

    Camera* Camera::mainCamera = NULL;
    Camera::Camera(unsigned int gameObjectId) : IComponent(gameObjectId)
    {
  //      projectionMatrix = glm::perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
        viewMatrix = glm::ortho(left, right, bottom, top);
    }
}