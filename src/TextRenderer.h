#pragma once
#include "API.h"
#include "Component.h"
#include "Font.h"
#include "Mesh.h"
#include "MeshLoaded.h"
#include "SpriteRendererProgram.h"

class API TextRenderer : public Component {
	SpriteRendererProgram* program;
	GLfloat* points;	
	GLuint vbo;
	GLuint ibo;
	Mesh* CreateMeshDataForRender();
	MeshLoaded textMesh;
	friend void windowChangedTextRenderer(void* obj, int w, int h);	
	void RefreshText();
	bool hasStarted = false;
public:
	float size = 1;
	vec3 color;
	Font* font;
	string text;
	TextRenderer();
	~TextRenderer();
	void Start();
	void Render();
	void SetText(string text);

	//Changing this will only be applied before Start on Component is called (before window->startRendering or the next Update if the object was create in the game loop)
	bool isStatic = true;
};

void windowChangedTextRenderer(void* obj, int w, int h);