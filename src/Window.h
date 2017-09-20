#pragma once
#define SDL_MAIN_HANDLED
#include "API.h"
#include <SDL2\SDL.h>
#include "Engine.h"
#include "Event.h"
#include "Input.h"
namespace Window
{
	API extern GLfloat aspectRatio;
	API extern int width;
	API extern int height;
	API extern Event<void, int, int> windowChangedSize;
	API extern Input input;
	API extern SDL_Window* window;
	API extern int Init(const char* windowName, const char* filePath, int x, int y, int width, int height, Uint32 flags = 0);
	API extern int StartRendering();
	API extern void Destroy();
};

