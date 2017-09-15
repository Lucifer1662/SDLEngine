#include "Engine.h"
#include "Entity.h"
#include <GL\glew.h>
#include "Mesh.h"
#include "vec3ui.h"


const char* Engine::localFilePath;

Engine::Engine(const char * localFilePath, Window* window, size_t initialEntities) : window(window)
{
	entities.resize(initialEntities);
	this->localFilePath = localFilePath;
}

Engine::~Engine()
{

	
}

int Engine::Init()
{
	

#pragma region OpenGlSetup
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
#pragma endregion
	//Create Default Shapes
#pragma region Create Square
	vec3 positions[4];
	positions[0] = vec3(-0.5f, -0.5f, 0);
	positions[1] = vec3(-0.5f, 0.5f, 0);
	positions[2] = vec3(0.5f, 0.5f, 0);
	positions[3] = vec3(0.5f, -0.5f, 0);

	size_t indices[6];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;


	Mesh squareMesh = Mesh(positions, 4, indices, 6);
	squareMesh.name = "Square";
	squareMesh.uvs.resize(4);
	squareMesh.uvs[0] = vec2(0, 0);
	squareMesh.uvs[1] = vec2(0, 1);
	squareMesh.uvs[2] = vec2(1, 1);
	squareMesh.uvs[3] = vec2(1, 0);

	squareMeshLoaded = LoadMesh(squareMesh);

	//Start all entities
	for (size_t i = 0; i < entities.size(); i++)
		entities[i]->Start();
	return 0;
}


int Engine::Render()
{
	for (size_t i = 0; i < entities.size(); i++)
		entities[i]->Update();

	for (size_t i = 0; i < entities.size(); i++)
		entities[i]->Render();

	return 0;
}

Entity * Engine::AddEntity(vec3 position, vec3 rotation, vec3 scale)
{
	Entity* entity = new Entity(this);
	entity->transform.position = position;
	entity->transform.rotation = rotation;
	entity->transform.scale = scale;
	entities.push_back(entity);
	return entity;
}

void Engine::RenderLoadedMesh(MeshLoaded meshLoaded)
{
	size_t i = 0;
	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glEnableVertexAttribArray(meshLoaded.atribCounts[i].x);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glVertexAttribPointer(meshLoaded.atribCounts[i].x, meshLoaded.atribCounts[i].y, GL_FLOAT, GL_FALSE,
			20, (void*)(meshLoaded.atribCounts[i].z));

	glDrawElements(GL_TRIANGLES, meshLoaded.indexCount, GL_UNSIGNED_INT, (void*)(meshLoaded.indexOffset));

	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
		glDisableVertexAttribArray(meshLoaded.atribCounts[i].x);
}

MeshLoaded* Engine::LoadMesh(Mesh mesh, GLuint vbo, GLuint ibo) {

	MeshLoaded* loadedMesh = new MeshLoaded();
	size_t countOfTotalAtribCounts = 0;
	size_t offset = 0;
	if (mesh.vertices.size() > 0) {
		//atribCounts.push_back(vec3ui(0, 3, offset));
		loadedMesh->atribCounts.push_back(vec3ui(loadedMesh->atribCounts.size(), sizeof(mesh.vertices[0]) / sizeof(mesh.vertices[0].x), offset));
		offset += sizeof(mesh.vertices[0]);
		countOfTotalAtribCounts += loadedMesh->atribCounts[loadedMesh->atribCounts.size() - 1].y;
	}
	if (mesh.uvs.size() > 0) {
		//atribCounts.push_back(vec3ui(1, 3, offset));
		loadedMesh->atribCounts.push_back(vec3ui(vec3ui(loadedMesh->atribCounts.size(), sizeof(mesh.uvs[0]) / sizeof(mesh.uvs[0].x), offset)));
		offset += sizeof(mesh.uvs[0]);
		countOfTotalAtribCounts += loadedMesh->atribCounts[loadedMesh->atribCounts.size() - 1].y;
	}

	for (size_t i = 0; i < mesh.additionalVertexDataStrides.size(); i++)
	{
			loadedMesh->atribCounts.push_back(vec3ui(vec3ui(loadedMesh->atribCounts.size(), mesh.additionalVertexDataStrides[i], offset)));
			offset += mesh.additionalVertexDataStrides[i];
			countOfTotalAtribCounts += loadedMesh->atribCounts[loadedMesh->atribCounts.size() - 1].y;
	}
	size_t totalAdditionalStride = 0;
	for (size_t i = 0; i < mesh.additionalVertexDataStrides.size(); i++)
		totalAdditionalStride += mesh.additionalVertexDataStrides[i];
	

	vector<GLfloat>vertices;
	vertices.resize(countOfTotalAtribCounts * mesh.vertices.size());
	size_t k = 0;
	size_t i = 0;
	size_t j;
	while (k < mesh.vertices.size())
	{
		vertices[i++] = mesh.vertices[k][0];
		vertices[i++] = mesh.vertices[k][1];
		vertices[i++] = mesh.vertices[k][2];

		if (mesh.uvs.size() > 0) {
			vertices[i++] = mesh.uvs[k][0];
			vertices[i++] = mesh.uvs[k][1];
		}
		for (j = 0; j < totalAdditionalStride; j++)
		{
			vertices[i++] = mesh.additionalVertexData[j + k * totalAdditionalStride];
		}
		k++;
	}
	
	loadedMesh->indexCount = mesh.indices.size();
	loadedMesh->vertexCount = mesh.vertices.size();
	//loadedMesh->indexOffset = sizeOfIndexes * sizeof(GLuint);
	//meshLs->vertexOffset = sizeOfVertexes * sizeof(GLfloat);
	loadedMesh->name = mesh.name;

	

	


	//---------------------Load Mesh Into Graphics------------------
	GLuint sizeOfVertexes = 0;
	GLuint sizeOfIndexes = 0;
	for (GLuint i = 0; i < meshLoads.size(); i++)
	{
		sizeOfVertexes += meshLoads[i]->vertexCount;
		sizeOfIndexes += meshLoads[i]->indexCount;
	}
	if (vbo == -1)
		vbo = vertexBuffer;
	if (ibo == -1)
		ibo = indexBuffer;

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	if (sizeOfVertexes > 0) {
		ResizeBuffers(sizeOfVertexes * sizeof(GLfloat), (sizeOfVertexes + vertices.size()) * sizeof(GLfloat), &vbo, GL_ARRAY_BUFFER);
		glBufferSubData(GL_ARRAY_BUFFER, sizeOfVertexes * sizeof(GLfloat), vertices.size() * sizeof(GLfloat), &(vertices[0]));
	}
	else
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &(vertices[0]), GL_DYNAMIC_DRAW);


	if (sizeOfIndexes > 0) {
		ResizeBuffers(sizeOfIndexes * sizeof(GLuint), (sizeOfIndexes + mesh.indices.size()) * sizeof(GLuint), &ibo, GL_ELEMENT_ARRAY_BUFFER);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndexes * sizeof(GLuint), mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]));
	}
	else
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]), GL_DYNAMIC_DRAW);


	GLuint vertModelOffset = 0;// mesh.vertices.size() * sizeof(GLfloat);


	offset = 0;
	if (loadedMesh->atribCounts.size() > 1)
		for (GLuint i = 0; i < loadedMesh->atribCounts.size(); i++) {
			loadedMesh->stride += sizeof(mesh.vertices[offset]) * loadedMesh->atribCounts[i].y;
			offset += loadedMesh->atribCounts[i].y;
			loadedMesh->atribCounts[i].z += vertModelOffset;
		}
	else
		loadedMesh->stride = 0;

	if (vbo == -1)
		meshLoads.push_back(loadedMesh);
	
	
	return loadedMesh;
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

}
