#pragma once
#include "API.h"
#include "Component.h"
#include <glm\glm.hpp>
#include <GL\glew.h>
using glm::mat4;

class API Camera : public Component {
	mat4 transformatiomMatrix;
	mat4 totalMatrix;
public:
	void SetCameraToOrthographic(GLfloat size, GLfloat near, GLfloat far);
	void SetCameraToPerspective(GLfloat angle, GLfloat near, GLfloat far);
	void SetAsMainCamera();
	mat4 GetTransformationMatrix();
	void Update();
};

