#pragma once
#include "API.h"
#include <memory>
#include "Mesh.h"
#include "_MeshLoaded.h"
#include "Engine.h"
using std::shared_ptr;


class API MeshLoaded :	public shared_ptr<_MeshLoaded>{
	bool isStatic = false;
	static void LoadDefaultMeshes();
	friend int Engine::Init(const char * localFilePath, size_t initialEntities);
	friend void Engine::Destroy();
	//this includes the default meshes as well
	static void DeleteStaticMeshes();
	static vector<MeshLoaded> loadedMeshes;
public:
	//friend int Engine::Init(const char * localFilePath, size_t initialEntities);
	


	MeshLoaded();
	~MeshLoaded();

	static MeshLoaded squareMeshLoaded;
	//if isStatic is true then the mesh will remain in memory even if not in use until the scene is reloaded
	//probably should use isStatic true if all instances using the shared are delete but then not long after mesh will be needed again and should not be deleted
	//if isStatic is false the mesh will remain in memory until last instance is using it
	//Note: the meshes name must be set as it is the unquie identifier
	static void LoadMeshShared(Mesh mesh ,MeshLoaded &loadedMesh, bool isStatic = false);
	static void LoadMeshShared(string name, MeshLoaded &loadedMesh);
	static void LoadMesh(Mesh mesh, MeshLoaded &loadedMesh);
	void ChangeLoadedMesh(Mesh mesh);	
};

