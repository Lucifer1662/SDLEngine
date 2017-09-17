#include "Window.h"
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>

Window::Window(const char* localFilePath) 
{
	
	string temp = localFilePath;
	temp.resize(temp.find_last_of('\\') + 1);
	temp.append("assets\\");
	const char* t = new char[temp.size()+1];
	memcpy((void*)t, temp.c_str(), temp.size()+1);
	
	engine = new Engine(t,this, 0);
}


Window::~Window()
{

}

int Window::Init(const char * windowName, const char* filePath, int x, int y, int width, int height, Uint32 flags)
{
	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
	window = SDL_CreateWindow("Fighting Game", x, y, width, height, SDL_WINDOW_OPENGL);
	this->width = width;
	this->height = height;
	aspectRatio = (float)width / (float)height;
	SDL_SetWindowResizable(window, SDL_TRUE);
	

	// Create our opengl context and attach it to our window
	SDL_GL_CreateContext(window);

	//SetOpenGLAttributes();

	// This makes our buffer swap syncronized with the monitor's vertical refresh
    SDL_GL_SetSwapInterval(1);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	// 3.2 is part of the modern versions of OpenGL, but most video cards whould be able to run it
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Turn on double buffering with a 24bit Z buffer.
	// You may need to change this to 16 or 32 for your system
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glewExperimental = GL_TRUE;
	glewInit();
	
	engine->Init();
	return 0;
}

int Window::StartRendering(){	
	SDL_Event windowEvent;
	glClearColor(0.5, 0.0, 1.0, 1.0);

	while (1) {
		SDL_PollEvent(&windowEvent);
		if (windowEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			SDL_GetWindowSize(window, &width, &height);
			aspectRatio = (float)width / (float)height;
			windowChangedSize.Call(width, height);
			glViewport(0, 0, width, height);
		}
		glClear(GL_COLOR_BUFFER_BIT);
		engine->Render();
		SDL_GL_SwapWindow(window);
		
	}
	return 0;
}
