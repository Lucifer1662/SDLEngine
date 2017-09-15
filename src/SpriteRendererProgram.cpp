#include "SpriteRendererProgram.h"
#include "Transform.h"
#include "Engine.h"
#include "Entity.h"
#include "Camera.h"

SpriteRendererProgram::SpriteRendererProgram()
{
}


SpriteRendererProgram::~SpriteRendererProgram()
{
}

GLuint SpriteRendererProgram::CreateProgram() {
	vector<ShaderSource> sources;
	ShaderSource source;
	source.filePath = "Shader/vertexShaderSprite.gl";
	source.shaderType = GL_VERTEX_SHADER;
	sources.push_back(source);

	source.filePath = "Shader/fragmentShaderSprite.gl";
	source.shaderType = GL_FRAGMENT_SHADER;
	sources.push_back(source);

	this->_CreateProgram(sources);
	Use();
	//GLuint p = glGetAttribLocation(program, "vPosition");
	glBindAttribLocation(program, 0, "vPosition");
	glBindAttribLocation(program, 1, "vUv");

	viewMatrixLocation = glGetUniformLocation(program, "viewMat");

	modelMatrixLocation = glGetUniformLocation(program, "modelMat");
//	uvAttributeLocation = glGetUniformLocation(program, "vUv");
	glUniform1i(glGetUniformLocation(program, "colorTexture"), 0);
	
	return _program;
}

void SpriteRendererProgram::PreRenderSetup() {
	Use(); 
	//glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, &(Engine::mainCamera->getViewMatrix()[0][0])); //update
}

void SpriteRendererProgram::SetTransform(Transform* transform) {
	glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, &(transform->entity->engine->mainCamera->GetTransformationMatrix() * transform->translationMatrix * transform->rotationMatrix * transform->scaleMatrix)[0][0]); //update
}

