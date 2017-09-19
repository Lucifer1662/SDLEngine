#pragma once
#define SDL_MAIN_HANDLED
#include "API.h"
#include <SDL2\SDL.h>
#include "Engine.h"
#include "Event.h"
#include "Input.h"
static class API Window
{
	
	
public:
	static GLfloat aspectRatio;
	static int width;
	static int height;
	static Event<void, int, int> windowChangedSize;
	static Input input;
	static SDL_Window* window;
	static int Init(const char* windowName, const char* filePath, int x, int y, int width, int height, Uint32 flags = 0);
	static int StartRendering();


};

