#include "TextRenderer.h"
#include "Mesh.h"
#include "Window.h"
#include "Engine.h"
using glm::vec3;
using glm::vec4;

#define VERTEXCOUNT 4

void TextRenderer::Start() {
	Window::windowChangedSize.Add(this, windowChangedTextRenderer);

	isStatic = false;
	program = Program::GetProgram<SpriteRendererProgram>();
	size = 100;


	//i should do static string
	//have max dynamic string
	//infinte string
	//glGenBuffers(1, &vbo);

	//glGenBuffers(1, &ibo);
	Mesh *mesh = CreateMeshDataForRender();
	if(isStatic)
		MeshLoaded::LoadMeshShared(*mesh, textMesh);
	else
		MeshLoaded::LoadMesh(*mesh, textMesh);
	delete mesh;
	hasStarted = true;
}

int p = 0;
void TextRenderer::Render() {
	p++;
	SetText(std::to_string(p));
	//the renderer creates an array of points with the Font characters
	//it handles the positions
	//the glsl program can handle creating the planes
	//entity->transform->UpdateModelMat();
	program->PreRenderSetup();
	program->SetTransform(entity->transform);
	font->texture->Bind(0);
	//need to make this on its own vbo and ibo
	Engine::RenderLoadedMesh(textMesh);
}




Mesh* TextRenderer::CreateMeshDataForRender() {
	/*Mesh* mesh = new Mesh();
	mesh->vertices.resize(text.size() * VERTEXCOUNT);
	mesh->indices.resize(text.size() * 6);
	mesh->uvs.resize(text.size() * VERTEXCOUNT);
	float cursor = 0;
	float line = 0;
	int texsizex = font->texture->width;
	int texsizey = font->texture->height;
	float w = (entity->engine->window->width /2) * font->GetSize()/size;
	float h = (entity->engine->window->height /2) * font->GetSize()/size;
	int i, k, u =0;
	for (int j = 0; j < text.size(); j++)
	{
		if (text[j] == '\n') {
			line += font->GetLineHeight();
			cursor = 0;
			continue;
		}

		FontCharacter fontCharacter = font->GetFontCharacter(text[j]);
		if (text[j] != ' ') {
			i = j * 4;

			vec3 mid = vec3((cursor + (float)fontCharacter.xoffset),
				((float)fontCharacter.yoffset - (float)line),
				entity->transform->position.z);


			vec2 adjSize = vec2((float)fontCharacter.width, (float)fontCharacter.height);
			vec2 uvadjSize = vec2(adjSize.x/texsizex,adjSize.y/texsizey);
			vec2 gUv = vec2((float)fontCharacter.x/texsizex, (float)fontCharacter.y/texsizey);

			

			mesh->uvs[u++] = vec2(gUv.x, gUv.y);
			mesh->uvs[u++] = vec2(gUv.x, gUv.y + uvadjSize.y);
			mesh->uvs[u++] = vec2(gUv.x + uvadjSize.x, gUv.y + uvadjSize.y);
			mesh->uvs[u++] = vec2(gUv.x + uvadjSize.x, gUv.y);
		
			//--------------------------------------------------
			vec3 p = (vec4(mid.x + adjSize.x, mid.y, mid.z, 1.0));
			vec2 uv = gUv + vec2(uvadjSize.x, 0);
			p.x /= w;
			p.y /= h;
			mesh->vertices[i] = p;
			//mesh->uvs[i] = uv;
			//--------------------------------------------------
			p = vec4(mid, 1);
			uv = gUv;
			p.x /= w;
			p.y /= h;
			mesh->vertices[i + 1] = p;
			//mesh->uvs[i + 1] = uv;
			//--------------------------------------------------
			mid.y += adjSize.y; // this cause the next two to only be done once and not twice
			p = (vec4(mid.x + adjSize.x, mid.y, 0.0, 1.0));
			uv = gUv + uvadjSize;
			p.x /= w;
			p.y /= h;
			mesh->vertices[i + 2] = p;
			//mesh->uvs[i + 2] = uv;
			//--------------------------------------------------
			p = (vec4(mid.x, mid.y, 0.0, 1.0));
			uv = gUv + vec2(0, uvadjSize.y);
			p.x /= w;
			p.y /= h;
			mesh->vertices[i + 3] = p;
			//mesh->uvs[i + 3] = uv;
			//--------------------------------------------------
			

			k = 6 * j;	
	
			mesh->indices[k] = i +1;
			mesh->indices[k + 1] = i ;
			mesh->indices[k + 2] = i + 2;
			mesh->indices[k + 3] = i + 3;
			mesh->indices[k + 4] = i + 1;
			mesh->indices[k + 5] = i + 2;
			
		}
		cursor += ((float)fontCharacter.xadvance );
	}
	
	*/
	float cursor = 0;
	float line = 0;
	int texsizex = font->texture->width;
	int texsizey = font->texture->height;
	

	Mesh *mesh = new Mesh();
	mesh->name = "Text";

	
	mesh->vertices = vector<vec3>(text.size() * 4);
	mesh->indices = vector<size_t>(text.size() * 6);
	mesh->uvs = vector<vec2>(text.size() * 4);
	//Create Verts
	size_t i = 0, l = 0, u = 0;
	for (int j = 0; j < text.size(); j++)
	{
		
		if (text[j] == '\n') {
			line += font->GetLineHeight();
			cursor = 0;
			continue;
		}

		FontCharacter fontCharacter = font->GetFontCharacter(text[j]);
		if (text[j] != ' ') {		
		// + (float)fontCharacter.xoffset
			cursor +=(float)fontCharacter.xoffset;
			vec3 mid = vec3((cursor/texsizex ),
							((float)fontCharacter.yoffset - (float)line)/texsizey,
				entity->transform->position.z);

			vec2 uvadjSize = vec2((float)fontCharacter.width / texsizex, (float)fontCharacter.height / texsizey);
			vec2 gUv = vec2((float)fontCharacter.x / texsizex, (float)fontCharacter.y / texsizey);

			mesh->indices[l++] = i;
			mesh->indices[l++] = i + 1;
			mesh->indices[l++] = i + 2;

			mesh->indices[l++] = i;
			mesh->indices[l++] = i + 2;
			mesh->indices[l++] = i + 3;

			mesh->uvs[u++] = vec2(gUv.x, gUv.y);
			mesh->uvs[u++] = vec2(gUv.x, gUv.y + uvadjSize.y);
			mesh->uvs[u++] = vec2(gUv.x + uvadjSize.x, gUv.y + uvadjSize.y);
			mesh->uvs[u++] = vec2(gUv.x + uvadjSize.x, gUv.y);


			mesh->vertices[i++] = vec3(mid.x, mid.y, 0);
			mesh->vertices[i++] = vec3(mid.x, mid.y + uvadjSize.y, 0);
			mesh->vertices[i++] = vec3(mid.x + uvadjSize.x, mid.y + uvadjSize.y, 0);
			mesh->vertices[i++] = vec3(mid.x + uvadjSize.x, mid.y, 0);


			
		
		}
		cursor += ((float)fontCharacter.xadvance);
	}
	
	return mesh;
}




TextRenderer::TextRenderer()
{
	font = new Font("Arial");
}

void TextRenderer::SetText(string text)
{
	if (isStatic && hasStarted) {
		printf("text is static and cannot be changed");
		return;
	}
	this->text = text;
	RefreshText();
}

void TextRenderer::RefreshText() {
	if (!hasStarted)
		return;
	Mesh* mesh = CreateMeshDataForRender();
	textMesh.ChangeLoadedMesh(*mesh);
	delete mesh;	
}


void windowChangedTextRenderer(void* obj, int w, int h) {
	((TextRenderer*)obj)->RefreshText();	
}


TextRenderer::~TextRenderer()
{
	delete font;
}
