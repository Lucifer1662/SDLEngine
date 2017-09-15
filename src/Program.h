#pragma once
#include "API.h"
#include "ShaderSource.h"
#include <string>
#include <vector>
#include <typeinfo>
#include <GL\glew.h>

using std::string;
using std::vector;

class API Program
{
	GLuint CreateShader(GLenum type, string source);

public:
	const GLuint &program;
	Program();
	virtual ~Program();
	void Use();

	virtual GLuint CreateProgram();
	virtual void PreRenderSetup() {};


	template <class T>
	static T* GetProgram() {
		for (GLuint i = 0; i < programs.size(); i++)
		{
			if (dynamic_cast<T*>(programs[i]) != NULL)
				return (T*)(programs[i]);
		}
		T* t = new T();
		t->CreateProgram();
		programs.push_back(t);
		return  (T*)programs[programs.size() - 1];
	}

	static void TermaniteAllPrograms();
	
	
protected:
	GLuint _program;
	GLuint _CreateProgram(vector<ShaderSource> sources);

private:
	static vector<Program*> programs;
};

