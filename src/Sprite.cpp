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
	int p = 0;
	_Texture2D::Delete(texture);
	std::cout << texture.use_count() << std::endl;
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
	Engine::RenderLoadedMesh(*MeshLoaded::squareMeshLoaded);
	if (Input::KeyDown('a'))
		entity->Destroy();
}
