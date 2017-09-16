#pragma once
#include "Texture2D.h"
#include <vector>
using std::vector;

class Texture2DShared :	public Texture2D{
	static vector<Texture2DShared> textures;
public:
	Texture2DShared();
	~Texture2DShared();
};

