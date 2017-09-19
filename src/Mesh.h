#pragma once

#include <vector>
#include <iostream>
#include <string>
#include <glm\glm.hpp>
#include <GL\glew.h>
using std::string;

using glm::vec2;
using glm::vec3;
using std::vector;

class Mesh {
public:
	vector<vec3> vertices;
	vector<size_t> indices;
	vector<vec2> uvs;
	vector<GLfloat> additionalVertexData;
	vector<size_t> additionalVertexDataStrides;
	string name;

	Mesh() {};

	Mesh(vec3* vertices, size_t vertSize, size_t* indices, size_t indexSize) {
		this->vertices = vector<vec3>(vertices,  vertices + vertSize);
		this->indices =  vector<size_t>(indices, indices  + indexSize);
	}

	Mesh(vec3* vertices, size_t vertSize,
		size_t* indices, size_t indexSize,
		GLfloat* additionalVertexData, size_t additionalVertexDataSize,
		vector<size_t> additionalVertexDataStrides) 
		: additionalVertexDataStrides(additionalVertexDataStrides) 
	{
		Mesh(vertices, vertSize, indices, indexSize);
		this->additionalVertexData = vector<GLfloat>(additionalVertexData, additionalVertexData + additionalVertexDataSize);
	}



};