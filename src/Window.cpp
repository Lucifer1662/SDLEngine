#include "Window.h"
#include <SDL2\SDL_image.h>


Window::Window(const char* localFilePath) : renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
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
	window = SDL_CreateWindow("Fighting Game", x, y, width, height, SDL_WINDOW_OPENGL);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


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
	aspectRatio = (float)width / (float)height;
	return 0;
}

int Window::StartRendering(){	
	engine->Init();
	while (1) {
		glClearColor(0.5, 0.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		
		//SDL_RenderClear(renderer);
		engine->Render();
		//SDL_RenderPresent(renderer);	
		SDL_GL_SwapWindow(window);
	}
	return 0;
}
