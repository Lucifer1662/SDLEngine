#include "Sprite.h"
#include "Engine.h"
#include "Entity.h"
#include "Input.h"
#include "Window.h"
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
	program->SetTransform(entity->transform);
	texture->Bind(0);
	Engine::RenderLoadedMesh(MeshLoaded::squareMeshLoaded);
	if (Input::KeyDown('a'))
		entity->Destroy();
}
