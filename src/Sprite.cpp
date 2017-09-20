#include "Sprite.h"
#include "Engine.h"
#include "Entity.h"
#include "Window.h"
#include "MeshLoaded.h"
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
}
