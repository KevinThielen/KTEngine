#include <GameObject.h>
#include <Components/Camera.h>

int kte::GameObject::availableId = 0;
kte::Camera* kte::Camera::mainCamera = NULL;