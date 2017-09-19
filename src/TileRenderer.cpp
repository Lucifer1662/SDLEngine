#include "TileRenderer.h"
#include "Entity.h"
#include "Engine.h"
#include "Mesh.h"

SpriteRendererProgram* TileRenderer::program;

void TileRenderer::Start(){
	program = Program::GetProgram<SpriteRendererProgram>();
}
void TileRenderer::Render(){
	program->PreRenderSetup();
	program->SetTransform(entity->transform);
	texture->Bind(0);
	Engine::RenderLoadedMesh(*loadedMesh);
	//entity->engine->squareMeshLoaded->indexOffset = 6;
	//entity->engine->RenderLoadedMesh(*entity->engine->squareMeshLoaded);
}

void TileRenderer::Init(size_t width, size_t height, GLfloat delta, size_t * tiles, Texture2D texture, float sizeOfSprite)
{



	this->texture = texture;
	Mesh mesh;
	mesh.vertices = vector<vec3>(width*height * 4);
	mesh.indices = vector<size_t>(width*height * 6);
	mesh.uvs = vector<vec2>(width*height * 4);
	//Create Verts
	size_t i = 0, l = 0, u = 0, r = 0;
	GLfloat y, x;

	for (y = 0; y < height*delta * 2; y += delta * 2) {
		for (x = 0; x < width*delta * 2; x += delta * 2)
		{

			mesh.indices[l++] = i;
			mesh.indices[l++] = i + 1;
			mesh.indices[l++] = i + 2;

			mesh.indices[l++] = i;
			mesh.indices[l++] = i + 2;
			mesh.indices[l++] = i + 3;


			mesh.vertices[i++] = vec3(x - delta, y - delta, 0);
			mesh.vertices[i++] = vec3(x - delta, y + delta, 0);
			mesh.vertices[i++] = vec3(x + delta, y + delta, 0);
			mesh.vertices[i++] = vec3(x + delta, y - delta, 0);

			GLfloat xx = (tiles[r] % width)*sizeOfSprite;
			GLfloat yy = (tiles[r] / height)*sizeOfSprite;
			mesh.uvs[u++] = vec2(xx, yy);
			mesh.uvs[u++] = vec2(xx, yy + sizeOfSprite);
			mesh.uvs[u++] = vec2(xx + sizeOfSprite, yy + sizeOfSprite);
			mesh.uvs[u++] = vec2(xx + sizeOfSprite, yy);
			r++;
		}
	}
	

	loadedMesh = Engine::LoadMesh(mesh);



}

TileRenderer::~TileRenderer()
{
	_Texture2D::Delete(texture);
	delete loadedMesh;
}
