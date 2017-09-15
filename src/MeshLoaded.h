#pragma once
#include <vec3ui.h>
#include <vector>
#include <string>

using std::string;
using std::vector;

struct MeshLoaded {
	GLuint vertexOffsetBytes;
	GLuint indexOffsetBytes;
	GLuint indexCount;
	GLuint vertexCount;
	GLuint stride;
	vector<vec3ui> atribCounts;
	string name;

};