#include "GameObject.h"
#include "Components/Camera.h"

unsigned int kte::GameObject::ID_COUNTER = 0;
kte::Camera* kte::Camera::mainCamera = nullptr;