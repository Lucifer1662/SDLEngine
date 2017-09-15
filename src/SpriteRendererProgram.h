#pragma once
#include "API.h"
#include "Program.h"
#include "Transform.h"

class API SpriteRendererProgram : public Program 
{
public:
	GLuint uvAttributeLocation;
	GLuint viewMatrixLocation;
	GLuint modelMatrixLocation;
	GLuint CreateProgram();
	void PreRenderSetup();

	void SetTransform(Transform* transform);
	SpriteRendererProgram();
	~SpriteRendererProgram();
};

