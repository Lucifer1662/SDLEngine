#include "Texture2DShared.h"


vector<Texture2DShared*> Texture2DShared::textures;
vector<const char*>	Texture2DShared::fileNames;

Texture2DShared::Texture2DShared()
{
}


Texture2DShared::~Texture2DShared()
{
}

Texture2DShared::Texture2DShared(const char * filePath):Texture2D(filePath)
{
}

Texture2DShared* Texture2DShared::Create(const char * filePath)
{
	//See if the texture has already been created and if so return it
	for (size_t i = 0; i < fileNames.size(); i++)
		if (fileNames[i] == filePath) 
			return textures[i];
		
	//else create a new texture2dshared
	Texture2DShared* text = new Texture2DShared(filePath);
	textures.push_back(text);
	fileNames.push_back(filePath);
	return text;
}
