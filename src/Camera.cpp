#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include "Entity.h"
#include "Engine.h"
#include "Window.h"
#include <GL\glew.h>
#include "Transform.h"

using glm::vec4;

void Camera::SetCameraToOrthographic(GLfloat size, GLfloat near, GLfloat far)
{
	transformatiomMatrix = glm::ortho(-size, size, size / entity->engine->window->aspectRatio, -size / entity->engine->window->aspectRatio, -near, -far);
}

void Camera::SetCameraToPerspective(GLfloat angle, GLfloat near, GLfloat far)
{
	transformatiomMatrix = glm::perspective(glm::degrees(angle), entity->engine->window->aspectRatio, -near, -far);
	
}

void Camera::SetAsMainCamera()
{
	entity->engine->mainCamera = this;
}


mat4 Camera::GetTransformationMatrix() {
	return transformatiomMatrix;
}

void Camera::Update() {
	entity->transform.position;
	totalMatrix = glm::lookAt(entity->transform.position, vec3(vec4(0,0,1,1) * entity->transform.rotationMatrix),vec3(0,1,0)) * transformatiomMatrix;
}