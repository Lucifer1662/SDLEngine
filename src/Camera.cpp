#include "Camera.h"
#include <glm\gtx\transform.hpp>
#include "Entity.h"
#include "Engine.h"
#include "Window.h"
#include <GL\glew.h>
#include "Transform.h"

using glm::vec4;

void Camera::Refresh()
{
	if(isOrtho)
		transformatiomMatrix = glm::ortho(-size, size, size / entity->engine->window->aspectRatio, -size / entity->engine->window->aspectRatio, -near, -far);
	else
		transformatiomMatrix = glm::perspective(glm::degrees(size), entity->engine->window->aspectRatio, -near, -far);
}

void Camera::SetCameraToOrthographic(GLfloat size, GLfloat near, GLfloat far)
{
	this->size = size;
	this->near = near;
	this->far = far;
	isOrtho = true;
	transformatiomMatrix = glm::ortho(-size, size, size / entity->engine->window->aspectRatio, -size / entity->engine->window->aspectRatio, -near, -far);
}

void Camera::SetCameraToPerspective(GLfloat angle, GLfloat near, GLfloat far)
{
	this->size = angle;
	this->near = near;
	this->far = far;
	isOrtho = false;
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
	entity->transform->position;
	totalMatrix = glm::lookAt(entity->transform->position, vec3(vec4(0,0,1,1) * entity->transform->rotationMatrix),vec3(0,1,0)) * transformatiomMatrix;
}

void Camera::Start()
{
	entity->engine->window->windowChangedSize.Add(this,windowChangedCameraRenderer);
}

void windowChangedCameraRenderer(void* obj, int w, int h) {
	((Camera*)(obj))->Refresh();
}