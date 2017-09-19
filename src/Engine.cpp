#include "Engine.h"
#include "Entity.h"
#include <GL\glew.h>
#include "Mesh.h"
#include "vec3ui.h"
#include "Transform.h"
#include "API.h"
#include "MeshLoaded.h"
#include "EngineTime.h"
using std::make_shared;

API vector<Entity*> Engine::entities;
API vector<Entity*> Engine::needsStarting;


API const char* Engine::localFilePath;
API Camera* Engine::mainCamera;



int Engine::Init(const char * localFilePath, size_t initialEntities)
{
	
	entities.resize(initialEntities);
	Engine::localFilePath = localFilePath;

/*
#pragma region OpenGlSetup
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
#pragma endregion

	glGenVertexArrays(1, &generalVAO);
	glBindVertexArray(generalVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 20,0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,20, (void*)12);
	*/



	MeshLoaded::LoadDefaultMeshes();

	

	return 0;
}

int Engine::Start()
{
	for (size_t i = 0; i < entities.size(); i++)
		entities[i]->Start();
	needsStarting.clear();

	return 0;
}



int Engine::Render()
{
	Time::Time();
	for (size_t i = 0; i < needsStarting.size(); i++)
		needsStarting[i]->Start();
	needsStarting.clear();

	for (size_t i = 0; i < entities.size(); i++)
		entities[i]->Update();

	for (size_t i = 0; i < entities.size(); i++)
		entities[i]->Render();
	return 0;
}

void Engine::Destroy()
{
	delete Engine::localFilePath;
	for (size_t i = 0; i < entities.size(); i++)
		delete entities[i];
	entities.clear();
	MeshLoaded::DeleteStaticMeshes();
}

Entity * Engine::AddEntity(vec3 position, vec3 rotation, vec3 scale)
{
	Entity* entity = new Entity();
	entity->transform->SetPosition(position);
	entity->transform->SetRotation(rotation);
	entity->transform->SetScale(scale);
	entities.push_back(entity);
	needsStarting.push_back(entity);
	return entity;
}

void Engine::DestroyEntity(Entity * entity)
{
	for (size_t i = 0; i < entities.size(); i++)
	{
		if (entities[i] == entity) {
			delete entities[i];
			entities[i] = entities[entities.size() - 1];
			entities.pop_back();
			return;
		}
	}
}



void Engine::RenderLoadedMesh(MeshLoaded &meshLoaded)
{
	/*size_t i = 0;
	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glEnableVertexAttribArray(meshLoaded.atribCounts[i].x);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glVertexAttribPointer(meshLoaded.atribCounts[i].x, meshLoaded.atribCounts[i].y, GL_FLOAT, GL_FALSE,
			meshLoaded.stride, (void*)(meshLoaded.atribCounts[i].z));
*/
	
	glBindVertexArray(*meshLoaded->vao);

	glDrawElements(GL_TRIANGLES, meshLoaded->indexCount, GL_UNSIGNED_INT, (void*)(meshLoaded->indexOffsetBytes));

//	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
//		glDisableVertexAttribArray(meshLoaded.atribCounts[i].x);
}


void Engine::ResizeBuffers(GLuint oldSize, GLuint newSize, GLuint* bo, GLenum buffer) {
	GLuint vbotemp;

	glBindBuffer(buffer, *bo);

	//create a temp buffer of type GL_COPY_READ_BUFFER
	glGenBuffers(1, &vbotemp);
	glBindBuffer(GL_COPY_READ_BUFFER, vbotemp);
	glBufferData(GL_COPY_READ_BUFFER, newSize, NULL, GL_STATIC_COPY);

	//copy data from vbo1 to it
	glCopyBufferSubData(buffer, GL_COPY_READ_BUFFER, 0, 0, oldSize);
	glBindBuffer(buffer, vbotemp);
	//glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);

	glDeleteBuffers(1, bo);
	bo[0] = vbotemp;
	glBindBuffer(buffer, vbotemp);

}

void Engine::RemoveSubBuffer(GLuint startPos, GLuint endPos, GLuint newSize, GLuint * bo, GLenum buffer)
{
	GLuint vbotemp;
	glBindBuffer(buffer, *bo);

	//create a temp buffer of type GL_COPY_READ_BUFFER
	glGenBuffers(1, &vbotemp);
	glBindBuffer(GL_COPY_READ_BUFFER, vbotemp);
	glBufferData(GL_COPY_READ_BUFFER, newSize, NULL, GL_STATIC_COPY);

	//copy data from vbo1 to it
	glCopyBufferSubData(buffer, GL_COPY_READ_BUFFER, 0, 0, startPos);
	glCopyBufferSubData(buffer, GL_COPY_READ_BUFFER, endPos, startPos, newSize - endPos);
	glBindBuffer(buffer, vbotemp);
	//glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);

	glDeleteBuffers(1, bo);
	bo[0] = vbotemp;
	glBindBuffer(buffer, vbotemp);
}

