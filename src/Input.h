#pragma once
#include <glm\glm.hpp>
#include <SDL2\SDL.h>
#include "API.h"
using glm::vec2;

static class API Input
{
public:
	static bool* keyDown;// [348];
	static vec2 mousePosition;
	static vec2 mouseMovement;

	static bool KeyDown(int key);

};

