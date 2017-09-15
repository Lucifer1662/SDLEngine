#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include "Entity.h"
#include "Engine.h"
#include "Window.h"
#include <GL\glew.h>

void Camera::SetCameraToOrthographic(GLfloat size)
{
	transformatiomMatrix = glm::ortho(-size, size, size / entity->engine->window->aspectRatio, -size / entity->engine->window->aspectRatio);
}

void Camera::SetCameraToPerspective(GLfloat angle, GLfloat near, GLfloat far)
{
	transformatiomMatrix = glm::perspective(glm::degrees(angle), entity->engine->window->aspectRatio, near, far);
}

void Camera::SetAsMainCamera()
{
	entity->engine->mainCamera = this;
}


mat4 Camera::GetTransformationMatrix() {
	return transformatiomMatrix;
}
