#pragma once
#define SDL_MAIN_HANDLED
#include "API.h"
#include <SDL2\SDL.h>
#include "Engine.h"

class API Window
{
	SDL_Window* window;
	

public:
	Window(const char* localFilePath);
	~Window();
	int Init(const char* windowName, const char* filePath, int x, int y, int width, int height, Uint32 flags = 0);
	int StartRendering();
	Engine* engine;
	SDL_Renderer* renderer;
	GLfloat aspectRatio;


};

