#pragma once
#include "API.h"
#include "_Texture2D.h"
#include <vector>
#include <memory>
using std::shared_ptr;
using std::make_shared;
using std::vector;

class API Texture2D : public shared_ptr<_Texture2D>
{
	static vector<Texture2D> textures;
public:
	Texture2D();
	~Texture2D();
	static void Create(string filePath, Texture2D &texture);
};

