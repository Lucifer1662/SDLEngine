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
class Camera;

class API Engine
{
	friend class Entity;
	vector<Entity*> entities;
	vector<Entity*> needsStarting;
	vector<MeshLoaded*> loadedMeshes;
public:
	static const char* localFilePath;
	GLuint vertexBuffer;
	GLuint indexBuffer;
	GLuint generalVAO;
	MeshLoaded* squareMeshLoaded;
	Camera* mainCamera;

	Engine(const char* localFilePath, Window* window, size_t initialEntities = 0);
	~Engine();	

	int Init();

	int Render();
	Window* window;

	void RenderLoadedMesh(MeshLoaded meshLoaded);

	MeshLoaded* LoadMeshCustom(Mesh mesh, GLuint &vbo, GLuint &ibo);
	MeshLoaded* LoadMesh(Mesh mesh);


	MeshLoaded* LoadDynamicMesh(Mesh mesh);
	void ChangeDynamicMesh(Mesh mesh, MeshLoaded* loadedMesh);


	void Engine::ResizeBuffers(GLuint oldSize, GLuint newSize, GLuint* bo, GLenum buffer);
	Entity* AddEntity(vec3 position = vec3(0,0,0), vec3 rotation = vec3(0,0,0), vec3 scale = vec3(1,1,1));

};

