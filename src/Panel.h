#pragma once
#include "API.h"
#include <SDL2\SDL.h>
#include "Component.h"
#include "Sprite.h"

class API Panel : public Sprite
{
public:
	int w = 100, h = 100;

	Panel();
	~Panel();


	void Render();
};

