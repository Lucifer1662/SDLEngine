#include "API.h"
#include "Component.h"
#include "SpriteRendererProgram.h"
#include "Texture2D.h"
#include "MeshLoaded.h"

class API TileRenderer : public Component {
	static SpriteRendererProgram* program;
	Texture2D* texture;
	MeshLoaded* loadedMesh;
public: 
	void Start();
	void Render();
	void Init(size_t width, size_t height, GLfloat delta, size_t* tiles, Texture2D* texture, float sizeOfSprite);

};