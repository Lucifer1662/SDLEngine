#pragma once
#include "API.h"
#include <glm\glm.hpp>
#include <vector>
#include <GL\glew.h>
#include "Entity.h"
#include "Camera.h"
using std::vector;
using glm::vec3;
class MeshLoaded;



namespace Engine
{
	extern vector<Entity*> entities;
	extern vector<Entity*> needsStarting;	

	extern API const char* localFilePath;
	extern API Camera* mainCamera;
	extern __declspec(dllimport) void (*LoadLevel)(size_t);

	API	int Init(const char * localFilePath, size_t initialEntities = 0);
	API	int Start();
	API	int Render();
	API	void Destroy();

	API	void RenderLoadedMesh(MeshLoaded &meshLoaded);

	API	void ResizeBuffers(GLuint oldSize, GLuint newSize, GLuint* bo, GLenum buffer);
	API	void RemoveSubBuffer(GLuint startPos, GLuint endPos, GLuint newSize, GLuint* bo, GLenum buffer);

	API	Entity* AddEntity(vec3 position = vec3(0,0,0), vec3 rotation = vec3(0,0,0), vec3 scale = vec3(1,1,1));
	API	void DestroyEntity(Entity* entity);

}
