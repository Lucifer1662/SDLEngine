#pragma once
#include "API.h"
#include "Component.h"
#include "SpriteRendererProgram.h"
#include "Texture2D.h"
class API Sprite : public Component
{
	static SpriteRendererProgram* program;
	
public:
	Sprite();
	~Sprite();
	void Start();
	void Render();
	Texture2D texture;
};

