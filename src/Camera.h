#pragma once
#include "API.h"
#include "Component.h"
#include <glm\glm.hpp>
#include <GL\glew.h>
using glm::mat4;

class API Camera : public Component {
	mat4 transformatiomMatrix;
	mat4 totalMatrix;
	friend void windowChangedCameraRenderer(void* obj, int w, int h);
	GLfloat size, near, far;
	void Refresh();
	bool isOrtho;
public:
	void SetCameraToOrthographic(GLfloat size, GLfloat near, GLfloat far);
	void SetCameraToPerspective(GLfloat angle, GLfloat near, GLfloat far);
	void SetAsMainCamera();
	mat4 GetTransformationMatrix();
	void Update();
	void Start();
};

void windowChangedCameraRenderer(void* obj, int w, int h);