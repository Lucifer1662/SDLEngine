#pragma once
#include <glm\glm.hpp>
#include <SDL2\SDL.h>
using glm::vec2;

class Input
{
public:
	bool* keyDown;// [348];
	vec2 mousePosition;
	vec2 mouseMovement;
	


	bool KeyDown(int key) {		
		//return *SDL_GetKeyState(key+1)[key] > 0;
		return keyDown[SDL_GetScancodeFromKey(key)];
	}

};

