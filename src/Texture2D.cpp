#include "Texture2D.h"
#include <SDL2\SDL_image.h>
#include <SDL2\SDL.h>
#include "Entity.h"
#include "Engine.h"
#include "Window.h"
#include <string>
#include <exception>
using std::string;
using std::make_shared;

vector<Texture2D> textures;


_Texture2D::_Texture2D()
{
}


_Texture2D::~_Texture2D()
{
		
}



void _Texture2D::Load(const char * filePath)
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

void _Texture2D::Bind(GLuint textureLocation)
{
	glActiveTexture(GL_TEXTURE0 + textureLocation);
	glBindTexture(GL_TEXTURE_2D,texture);
	
}


Texture2D _Texture2D::Create(const char * filePath)
{
	//See if the texture has already been created and if so return it
	for (size_t i = 0; i < textures.size(); i++)
		if (textures[i]->fileName == filePath) {
			return textures[i];
		}

	//else create a new texture2dshared
	Texture2D text = make_shared<_Texture2D>();
	text->Load(filePath);
	//textures.push_back(text);
	text->fileName = filePath;
	return text;
}

void _Texture2D::Delete(Texture2D texture) {
	if (texture.use_count() == 2) {
		for (size_t i = 0; i < textures.size(); i++)
			if (textures[i].get() == texture.get()) {
				textures[i] = textures[textures.size() - 1];
				textures.pop_back();
				return;
			}
	}
}