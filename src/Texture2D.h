#pragma once
#include "API.h"
#include <SDL2\SDL.h>
#include <GL\glew.h>
class API Texture2D
{
	//SDL_Texture* texture;
	GLuint texture;
public:
	Texture2D();
	~Texture2D();
	Texture2D(const char* filePath);
	void Bind(GLuint textureLocation);
	int width, height;
};

