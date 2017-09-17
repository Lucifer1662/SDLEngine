#include "Engine.h"
#include "Entity.h"
#include <GL\glew.h>
#include "Mesh.h"
#include "vec3ui.h"
#include "Transform.h"


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

	glGenVertexArrays(1, &generalVAO);
	glBindVertexArray(generalVAO);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 20,0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,20, (void*)12);






	//Create Default Shapes
	
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

	return 0;
}



int Engine::Render()
{
	for (size_t i = 0; i < needsStarting.size(); i++)
		entities[i]->Start();
	needsStarting.clear();

	for (size_t i = 0; i < entities.size(); i++)
		entities[i]->Update();

	for (size_t i = 0; i < entities.size(); i++)
		entities[i]->Render();

	return 0;
}

Entity * Engine::AddEntity(vec3 position, vec3 rotation, vec3 scale)
{
	Entity* entity = new Entity(this);
	entity->transform->SetPosition(position);
	entity->transform->SetRotation(rotation);
	entity->transform->SetScale(scale);
	entities.push_back(entity);
	needsStarting.push_back(entity);
	return entity;
}



void Engine::RenderLoadedMesh(MeshLoaded meshLoaded)
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
	
	glBindVertexArray(*meshLoaded.vao);

	glDrawElements(GL_TRIANGLES, meshLoaded.indexCount, GL_UNSIGNED_INT, (void*)(meshLoaded.indexOffsetBytes));

//	for (i = 0; i < meshLoaded.atribCounts.size(); i++)
//		glDisableVertexAttribArray(meshLoaded.atribCounts[i].x);
}

//Idk If this works yet
MeshLoaded* Engine::LoadMeshCustom(Mesh mesh, GLuint &vbo, GLuint &ibo) {
	MeshLoaded* loadedMesh = new MeshLoaded();

/*	size_t countOfTotalAtribCounts = 0;
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


	for (GLuint i = 0; i < loadedMeshes.size(); i++)
	{
		loadedMesh->vertexOffsetBytes += loadedMeshes[i]->vertexCount;
		loadedMesh->indexOffsetBytes += loadedMeshes[i]->indexCount;
	}
	GLuint sizeOfVertexes = loadedMesh->vertexOffsetBytes + loadedMesh->vertexCount;
	GLuint sizeOfIndexes = loadedMesh->indexOffsetBytes + loadedMesh->indexCount;;

	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &(vertices[0]), GL_DYNAMIC_DRAW);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]), GL_DYNAMIC_DRAW);


	offset = 0;
	if (loadedMesh->atribCounts.size() > 1)
		for (GLuint i = 0; i < loadedMesh->atribCounts.size(); i++) {
			loadedMesh->stride += sizeof(GL_FLOAT) * loadedMesh->atribCounts[i].y;
			offset += loadedMesh->atribCounts[i].y;
		}
	else
		loadedMesh->stride = 0;
		*/
	return loadedMesh;
}

MeshLoaded* Engine::LoadMesh(Mesh mesh) {
	MeshLoaded* loadedMesh = new MeshLoaded();

	

	vector<GLfloat>vertices;
	vertices.resize(5 * mesh.vertices.size());
	size_t k = 0,i = 0;
	while (k < mesh.vertices.size())
	{
		vertices[i++] = mesh.vertices[k][0];
		vertices[i++] = mesh.vertices[k][1];
		vertices[i++] = mesh.vertices[k][2];

		if (mesh.uvs.size() > 0) {
			vertices[i++] = mesh.uvs[k][0];
			vertices[i++] = mesh.uvs[k][1];
		}
		k++;
	}
	
	loadedMesh->indexCount = mesh.indices.size();
	loadedMesh->vertexCount = vertices.size();	


	//---------------------Load Mesh Into Graphics------------------
	
	GLuint vertexOffsetBytes = 0;
	for (GLuint i = 0; i < loadedMeshes.size(); i++)
	{
		vertexOffsetBytes += loadedMeshes[i]->vertexCount;
		loadedMesh->indexOffsetBytes += loadedMeshes[i]->indexCount;
	}
	loadedMesh->vertexOffset = vertexOffsetBytes;
	vertexOffsetBytes *= sizeof(GLfloat);
	loadedMesh->indexOffsetBytes *= sizeof(GLuint);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	if (loadedMeshes.size() >= 1) {
		ResizeBuffers(vertexOffsetBytes, vertexOffsetBytes + vertices.size() * sizeof(GLfloat), &vertexBuffer, GL_ARRAY_BUFFER);
		glBufferSubData(GL_ARRAY_BUFFER, vertexOffsetBytes, vertices.size() * sizeof(GLfloat), &(vertices[0]));

		GLuint indexOffset = loadedMesh->vertexOffset/5;
		for (size_t i = 0; i < mesh.indices.size(); i++)
			mesh.indices[i] += indexOffset;
		
		ResizeBuffers(loadedMesh->indexOffsetBytes, loadedMesh->indexOffsetBytes + mesh.indices.size() * sizeof(GLuint), &indexBuffer, GL_ELEMENT_ARRAY_BUFFER);
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, loadedMesh->indexOffsetBytes, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]));
		
		glBindVertexArray(generalVAO);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, 0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
		glBindVertexArray(0);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &(vertices[0]), GL_DYNAMIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]), GL_DYNAMIC_DRAW);
	}
	
	loadedMesh->vao = &generalVAO;
	loadedMeshes.push_back(loadedMesh);
	return loadedMesh;
}

MeshLoaded* Engine::LoadDynamicMesh(Mesh mesh) {
	MeshLoaded* loadedMesh = new MeshLoaded();
	
	vector<GLfloat>vertices;
	vertices.resize(5 * mesh.vertices.size());
	size_t k = 0, i = 0;
	while (k < mesh.vertices.size())
	{
		vertices[i++] = mesh.vertices[k][0];
		vertices[i++] = mesh.vertices[k][1];
		vertices[i++] = mesh.vertices[k][2];

		if (mesh.uvs.size() > 0) {
			vertices[i++] = mesh.uvs[k][0];
			vertices[i++] = mesh.uvs[k][1];
		}
		k++;
	}

	loadedMesh->indexCount = mesh.indices.size();
	loadedMesh->vertexCount = vertices.size();
	loadedMesh->vertexOffset = 0;
	loadedMesh->indexOffsetBytes = 0;

	//---------------------Load Mesh Into Graphics------------------
	GLuint vbo, ibo;

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &(vertices[0]), GL_DYNAMIC_DRAW);

	glGenBuffers(1, &ibo);	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]), GL_DYNAMIC_DRAW);
	
	
	loadedMesh->vao = new GLuint();
	glGenVertexArrays(1, loadedMesh->vao);
	glBindVertexArray(*loadedMesh->vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 20, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (void*)12);
	glBindVertexArray(0);

	return loadedMesh;
}

void Engine::ChangeDynamicMesh(Mesh mesh, MeshLoaded* loadedMesh)
{
	vector<GLfloat>vertices;
	vertices.resize(5 * mesh.vertices.size());
	size_t k = 0, i = 0;
	while (k < mesh.vertices.size())
	{
		vertices[i++] = mesh.vertices[k][0];
		vertices[i++] = mesh.vertices[k][1];
		vertices[i++] = mesh.vertices[k][2];

		if (mesh.uvs.size() > 0) {
			vertices[i++] = mesh.uvs[k][0];
			vertices[i++] = mesh.uvs[k][1];
		}
		k++;
	}

	loadedMesh->indexCount = mesh.indices.size();
	loadedMesh->vertexCount = vertices.size();
	loadedMesh->vertexOffset = 0;
	loadedMesh->indexOffsetBytes = 0;

	//---------------------Load Mesh Into Graphics------------------
	glBindVertexArray(*loadedMesh->vao);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &(vertices[0]), GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]), GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
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
