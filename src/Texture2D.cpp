#include "Texture2D.h"


vector<Texture2D> Texture2D::textures;


Texture2D::Texture2D(): shared_ptr<_Texture2D>(make_shared<_Texture2D>())
{
}


Texture2D::~Texture2D()
{
	if (use_count() == 2) {
		for (size_t i = 0; i < textures.size(); i++)
			if (textures[i] == *this) {
				textures[i] = textures[textures.size() - 1];
				textures.pop_back();
				return;
			}
	}


}

void Texture2D::Create(string filePath, Texture2D &texture)
{
	//See if the texture has already been created and if so return it
	for (size_t i = 0; i < textures.size(); i++)
		if (textures[i]->fileName == filePath) {
			texture = textures[i];
			return;
		}

	//else create a new texture2dshared
	
	texture->Load(filePath);
	//textures.push_back(text);
	texture->fileName = filePath;
}