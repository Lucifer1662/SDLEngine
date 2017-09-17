#include "Texture2D.h"
#include <SDL2\SDL_image.h>
#include <SDL2\SDL.h>
#include "Entity.h"
#include "Engine.h"
#include "Window.h"
#include <string>
using std::string;


Texture2D::Texture2D()
{
}


Texture2D::~Texture2D()
{

}

Texture2D::Texture2D(const char * filePath)
{

	
	string s = string(Engine::localFilePath).append(filePath);
	SDL_Surface* img = IMG_Load(string(Engine::localFilePath).append(filePath).c_str());
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_WRAP_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_WRAP_BORDER);
	width = img->w;
	height = img->h;
}

void Texture2D::Bind(GLuint textureLocation)
{
	glActiveTexture(GL_TEXTURE0 + textureLocation);
	glBindTexture(GL_TEXTURE_2D,texture);
	
}
