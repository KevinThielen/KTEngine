#include "GameObject.h"
#include "Components/Camera.h"
#include "Input.h"

unsigned int kte::GameObject::ID_COUNTER = 0;
kte::Camera* kte::Camera::mainCamera = nullptr;
kte::Window* kte::Input::window = nullptr;