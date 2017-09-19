#pragma once
#include <glm\glm.hpp>
#include <SDL2\SDL.h>
using glm::vec2;

static class Input
{
public:
	static bool* keyDown;// [348];
	static vec2 mousePosition;
	static vec2 mouseMovement;
	


	static bool KeyDown(int key) {		
		//return *SDL_GetKeyState(key+1)[key] > 0;
		return keyDown[SDL_GetScancodeFromKey(key)];
	}

};

