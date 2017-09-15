#pragma once
#include "API.h"
#include <glm\glm.hpp>
#include <vector>
#include <GL\glew.h>
#include "Mesh.h"
#include "MeshLoaded.h"

using std::vector;
using glm::vec3;
class Entity;
class Window;

class API Engine
{
	
	vector<Entity*> entities;

public:
	static const char* localFilePath;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint generalVAO;
	MeshLoaded* squareMeshLoaded;
	vector<MeshLoaded*> meshLoads;


	Engine(const char* localFilePath, Window* window, size_t initialEntities = 0);
	~Engine();	

	int Init();
	int Render();
	Window* window;

	void RenderLoadedMesh(MeshLoaded meshLoaded);

	MeshLoaded* LoadMesh(Mesh mesh, GLuint vbo = -1, GLuint ibo = -1);
	void Engine::ResizeBuffers(GLuint oldSize, GLuint newSize, GLuint* bo, GLenum buffer);
	Entity* AddEntity(vec3 position = vec3(0,0,0), vec3 rotation = vec3(0,0,0), vec3 scale = vec3(0,0,0));
	
};

