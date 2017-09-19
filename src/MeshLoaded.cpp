#include "MeshLoaded.h"
#include "Engine.h"
using std::make_shared;

API vector<MeshLoaded> MeshLoaded::loadedMeshes;
API MeshLoaded MeshLoaded::squareMeshLoaded;

MeshLoaded::MeshLoaded() : shared_ptr<_MeshLoaded>(make_shared<_MeshLoaded>())
{
}

MeshLoaded::~MeshLoaded()
{
	//if isnt static and all objects using the mesh are done do the fine removal
	if(!isStatic && use_count() == 2){
		for (size_t i = 0; i < loadedMeshes.size(); i++)
		{
			if (loadedMeshes[i] == *this) {
				loadedMeshes[i] = loadedMeshes[loadedMeshes.size() - 1];
				loadedMeshes.pop_back();
				return;
			}
		}
	}
}

void MeshLoaded::LoadDefaultMeshes()
{
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

	MeshLoaded::LoadMeshShared(squareMesh, MeshLoaded::squareMeshLoaded);
	int l = 0;
}

void MeshLoaded::DeleteStaticMeshes()
{
	loadedMeshes.clear();
}

void MeshLoaded::LoadMesh(Mesh mesh, MeshLoaded &loadedMesh) {
	loadedMesh->name = mesh.name;
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
	loadedMesh->buffers.resize(2);
	loadedMesh->buffers[0] = vbo;
	loadedMesh->buffers[1] = ibo;


}

void MeshLoaded::LoadMeshShared(Mesh mesh, MeshLoaded &loadedMesh, bool isStatic) {
	for (size_t i = 0; i < loadedMeshes.size(); i++)
	{
		if (loadedMeshes[i]->name == mesh.name) {
			loadedMesh = loadedMeshes[i];
			return;
		}
		
	}
	LoadMesh(mesh, loadedMesh);
	loadedMesh.isStatic = isStatic;
	loadedMeshes.push_back(loadedMesh);
	loadedMeshes[loadedMeshes.size() - 1] = loadedMesh;

	/*_MeshLoaded* loadedMesh = new _MeshLoaded();



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
	/*	for (GLuint i = 0; i < loadedMeshes.size(); i++)
	{
	vertexOffsetBytes += loadedMeshes[i]->vertexCount;
	loadedMesh->indexOffsetBytes += loadedMeshes[i]->indexCount;
	}
	*/
	//vertexOffsetBytes *= sizeof(GLfloat);
	//loadedMesh->indexOffsetBytes *= sizeof(GLuint);
	/*
	GLuint vertexOffsetBytes = vertexBufferLengthBytes;
	vertexBufferLengthBytes += vertices.size() * sizeof(GLfloat);

	loadedMesh->vertexOffset = vertexOffsetBytes/sizeof(GLfloat);
	loadedMesh->indexOffsetBytes = indexBufferLengthBytes;
	indexBufferLengthBytes += loadedMesh->indexCount*sizeof(GLuint);


	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	if (loadedMeshes.size() >= 1) {
	ResizeBuffers(vertexOffsetBytes, vertexBufferLengthBytes, &vertexBuffer, GL_ARRAY_BUFFER);
	glBufferSubData(GL_ARRAY_BUFFER, vertexOffsetBytes, vertices.size() * sizeof(GLfloat), &(vertices[0]));


	GLuint indexOffset = loadedMesh->vertexOffset/5;
	for (size_t i = 0; i < mesh.indices.size(); i++)
	mesh.indices[i] += indexOffset;

	ResizeBuffers(loadedMesh->indexOffsetBytes, indexBufferLengthBytes, &indexBuffer, GL_ELEMENT_ARRAY_BUFFER);
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
	loadedMesh->buffers.resize(2);
	loadedMesh->buffers[0] = &vertexBuffer;
	loadedMesh->buffers[1] = &indexBuffer;

	loadedMeshes.push_back(loadedMesh);
	return loadedMesh;
	*/
}

void MeshLoaded::LoadMeshShared(string name, MeshLoaded &loadedMesh)
{
	for (size_t i = 0; i < loadedMeshes.size(); i++)
	{
		if (loadedMeshes[i]->name == name) {
			loadedMesh = loadedMeshes[i];
			return;
		}
	}
	loadedMesh = MeshLoaded();
}

void MeshLoaded::ChangeLoadedMesh(Mesh mesh)
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

	get()->indexCount = mesh.indices.size();
	get()->vertexCount = vertices.size();
	get()->vertexOffset = 0;
	get()->indexOffsetBytes = 0;

	//---------------------Load Mesh Into Graphics------------------
	glBindVertexArray(*get()->vao);
	GLuint g = get()->buffers[0], h = get()->buffers[1];
	

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &(vertices[0]), GL_DYNAMIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.indices.size() * sizeof(GLuint), &(mesh.indices[0]), GL_DYNAMIC_DRAW);
	glBindVertexArray(0);
}



