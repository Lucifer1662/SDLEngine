#pragma once
#include "API.h"
#include <GL\glew.h>
#include <string>

using std::string;

class API _Texture2D
{
	friend class Texture2D;
	GLuint texture;		
	void Load(string filePath);
	
public:		
	_Texture2D();
	void Bind(GLuint textureLocation);
	int width, height;
	~_Texture2D();
	string fileName;
};

