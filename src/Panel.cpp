#include "Panel.h"
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include "Window.h"
#include "Entity.h"
#include "Transform.h"
Panel::Panel()
{

}

Panel::~Panel()
{

}



void Panel::Render()
{
	SDL_Rect rect = SDL_Rect();
	rect.x = entity->transform->position.x;
	rect.w = w;
	rect.y = entity->transform->position.y;
	rect.h = h;
	//SDL_RenderCopy(entity->engine->window->renderer, texture, &clipRectangle, &rect);
	//SDL_RenderCopyEx(entity->engine->window->renderer, texture, &clipRectangle, &rect, entity->transform->rotation.z, NULL, SDL_FLIP_NONE);
}
