#include "Texture2D.h"
#include <SDL2\SDL_image.h>
#include <SDL2\SDL.h>
#include "Entity.h"
#include "Engine.h"
#include "Window.h"
#include <string>
#include <exception>
#include <SOIL\SOIL.h>
using std::string;
using std::make_shared;

vector<Texture2D> textures;


_Texture2D::_Texture2D()
{
}


_Texture2D::~_Texture2D()
{
	
}



void _Texture2D::Load(string filePath)
{
	
	fileName = filePath;
//	texture = SOIL_load_OGL_texture((Engine::localFilePath + fileName).c_str(), SOIL_LOAD_AUTO,
//		SOIL_CREATE_NEW_ID,
//		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	int channels;
	unsigned char* data = SOIL_load_image((Engine::localFilePath + fileName).c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);

	texture = SOIL_create_OGL_texture(data, width, height, channels, SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	SOIL_free_image_data(data);
	/*SDL_Surface* img = IMG_Load((Engine::localFilePath + fileName).c_str());
	
	Uint8* pixels = new Uint8[img->w*img->h * 4];
	memcpy(pixels, img->pixels, img->w*img->h * 4);
	

	size_t widthInVec = img->w * 4;
	size_t rowLength = widthInVec * sizeof(Uint8);
	Uint8* temp = new Uint8[rowLength];
	for (size_t i = 0; i < img->h/2; i++)
	{
		memcpy(temp, (void*)&pixels[i * widthInVec], rowLength);
		memcpy((void*)&pixels[i*widthInVec], (void*)&pixels[(img->h-i-1)*widthInVec], rowLength);
		memcpy((void*)&pixels[(img->h-i-1)*widthInVec], temp, rowLength);
	}
	delete[] temp;
	
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_WRAP_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_WRAP_BORDER);
	width = img->w;
	height = img->h;
	glBindTexture(GL_TEXTURE_2D, 0);
	delete[] pixels;
	SDL_FreeSurface(img);*/
}

void _Texture2D::Bind(GLuint textureLocation)
{
	glActiveTexture(GL_TEXTURE0 + textureLocation);
	glBindTexture(GL_TEXTURE_2D,texture);
	
}


