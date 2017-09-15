#pragma once
#include "API.h"
#include <SDL2\SDL.h>
#include "Component.h"

class API Panel : public Component
{
	SDL_Texture* texture;
	size_t width, height;
public:
	int w = 100, h = 100;
	SDL_Rect clipRectangle;
	Panel();
	~Panel();
	void AddConstTexture(const char* file);

	void Render();
};

