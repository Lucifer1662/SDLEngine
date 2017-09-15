#include "Sprite.h"
#include "Engine.h"
#include "Entity.h"
SpriteRendererProgram* Sprite::program;

Sprite::Sprite()
{
}


Sprite::~Sprite()
{
}

void Sprite::Start()
{
	program = Program::GetProgram<SpriteRendererProgram>();
}

void Sprite::Render()
{
	program->PreRenderSetup();
	program->SetTransform(&entity->transform);
	texture.Bind(0);
	entity->engine->RenderLoadedMesh(*entity->engine->squareMeshLoaded);
}
