#pragma once
#include "API.h"
#include <memory>
#include <SDL2\SDL.h>
#include <GL\glew.h>
using std::shared_ptr;
using std::make_shared;
#define Texture2D shared_ptr<_Texture2D>

class API _Texture2D
{
	const char* fileName;
	GLuint texture;	
	
	void Load(const char* filePath);
public:	
	_Texture2D();
	void Bind(GLuint textureLocation);
	int width, height;
	~_Texture2D();
	static Texture2D Create(const char* filePath);
	static void Delete(Texture2D);
};

