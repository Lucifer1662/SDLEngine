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

static class API Engine
{
	friend class Entity;
	static vector<Entity*> entities;
	static vector<Entity*> needsStarting;
	static vector<MeshLoaded*> loadedMeshes;
public:
	static const char* localFilePath;
	static GLuint vertexBuffer;
	static GLuint indexBuffer;
	static GLuint generalVAO;
	static Camera* mainCamera;


	static int Init(const char * localFilePath, size_t initialEntities = 0);
	static int Start();
	static int Render();
	static void Destroy();

	static void RenderLoadedMesh(MeshLoaded meshLoaded);

	static MeshLoaded* LoadMeshCustom(Mesh mesh, GLuint &vbo, GLuint &ibo);
	static MeshLoaded* LoadMesh(Mesh mesh);


	static MeshLoaded* LoadDynamicMesh(Mesh mesh);
	static void ChangeDynamicMesh(Mesh mesh, MeshLoaded* loadedMesh);

	static void Engine::ResizeBuffers(GLuint oldSize, GLuint newSize, GLuint* bo, GLenum buffer);

	static Entity* AddEntity(vec3 position = vec3(0,0,0), vec3 rotation = vec3(0,0,0), vec3 scale = vec3(1,1,1));
	static void DestroyEntity(Entity* entity);

};
