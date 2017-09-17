#pragma once
#include <vec3ui.h>
#include <vector>
#include <string>

using std::string;
using std::vector;

struct MeshLoaded {
	GLuint vertexOffset;
	GLuint indexOffsetBytes;
	GLuint indexCount;
	GLuint vertexCount;
	GLuint* vao;
	vector<GLuint*> buffers;
	//GLuint stride;
	//vector<vec3ui> atribCounts;
	//string name;

};