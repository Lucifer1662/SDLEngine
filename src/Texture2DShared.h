#pragma once
#include "API.h"
#include "Texture2D.h"
#include <vector>
using std::vector;

class API Texture2DShared :	public Texture2D{
	static vector<Texture2DShared*> textures;
	static vector<const char*> fileNames;

	Texture2DShared(const char* filePath);
	Texture2DShared();
	~Texture2DShared();
public:
	
	static Texture2DShared* Create(const char* filePath);
};

