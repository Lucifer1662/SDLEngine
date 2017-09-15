#include "Panel.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "Window.h"
#include "Entity.h"
#include "Transform.h"
Panel::Panel()
{
	clipRectangle.x = clipRectangle.y = 0;	
}

Panel::~Panel()
{

}

void Panel::AddConstTexture(const char * file)
{

	texture = IMG_LoadTexture(entity->engine->window->renderer, "C:\\Users\\lhawk\\Stuff\\VisualStudio\\SDLEngine\\FightingGame\\bin\\Debug\\x86\\assets\\texture1.png");
	SDL_QueryTexture(texture,NULL,NULL,&clipRectangle.w,&clipRectangle.h);
}

void Panel::Render()
{
	SDL_Rect rect = SDL_Rect();
	rect.x = entity->transform.position.x;
	rect.w = w;
	rect.y = entity->transform.position.y;
	rect.h = h;
	//SDL_RenderCopy(entity->engine->window->renderer, texture, &clipRectangle, &rect);
	SDL_RenderCopyEx(entity->engine->window->renderer, texture, &clipRectangle, &rect, entity->transform.rotation.z, NULL, SDL_FLIP_NONE);
}
