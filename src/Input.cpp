#include "Input.h"


bool* Input::keyDown;// [348];
vec2 Input::mousePosition;
vec2 Input::mouseMovement;

bool Input::KeyDown(int key) {
	return keyDown[SDL_GetScancodeFromKey(key)];
}