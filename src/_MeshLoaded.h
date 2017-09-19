#pragma once
#include <vec3ui.h>
#include <vector>
#include <string>
#include <GL\glew.h>
using std::string;
using std::vector;

struct _MeshLoaded {
	GLuint vertexOffset;
	GLuint indexOffsetBytes;
	GLuint indexCount;
	GLuint vertexCount;
	GLuint* vao;
	vector<GLuint> buffers;
	string name;
	~_MeshLoaded();
private:
	void RemoveFromGPU();

};